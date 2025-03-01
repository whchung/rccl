/*************************************************************************
 * Copyright (c) 2015-2022, NVIDIA CORPORATION. All rights reserved.
 *
 * See LICENSE.txt for license information
 ************************************************************************/

#include "channel.h"
#include "param.h"
#include "gdrwrap.h"

ncclResult_t initChannel(struct ncclComm* comm, int channelId) {
  struct ncclChannel* channel = &comm->channels[channelId];
  if (channel->id != -1) return ncclSuccess;

  int nRanks = comm->nRanks;
  channel->id = channelId;
  channel->workFifoSent = 0;

  NCCLCHECK(ncclStrongStreamAcquireUncaptured(&comm->deviceStream));

  // The extra on nRanks+1 is for collnet root (i.e. network)
  channel->peers = ncclMemoryStackAlloc<struct ncclChannelPeer>(&comm->memPermanent, nRanks+1);
  NCCLCHECK(ncclCudaCallocAsync(&channel->devPeers, nRanks+1, comm->deviceStream.stream));
  ncclCommPushCudaFree(comm, channel->devPeers);

  channel->ring.userRanks = ncclMemoryStackAlloc<int>(&comm->memPermanent, nRanks);
  NCCLCHECK(ncclCudaCallocAsync(&channel->devRingUserRanks, nRanks, comm->deviceStream.stream));
  ncclCommPushCudaFree(comm, channel->devRingUserRanks);

  NCCLCHECK(ncclStrongStreamRelease(ncclCudaGraphNull(), &comm->deviceStream));

  for (int r=0; r < nRanks+1; ++r) {
    for (int b=0; b < NCCL_MAX_CONNS; b++) {
      channel->peers[r].send[b].comm = comm;
      channel->peers[r].recv[b].comm = comm;
    }
  }

  return ncclSuccess;
}

ncclResult_t freeChannel(struct ncclChannel* channel, int nRanks) {
  if (channel->id == -1) return ncclSuccess;

  // Free transport proxy resources
  // Note: free all send resources first due to CollNet arrangement
  for (int r=0; r<nRanks+1; r++) {
    struct ncclChannelPeer* peer = channel->peers+r;
    for (int b=0; b<NCCL_MAX_CONNS; b++) {
      if (peer->send[b].transportComm) NCCLCHECK(peer->send[b].transportComm->free(peer->send+b));
    }
  }
  for (int r=0; r<nRanks+1; r++) {
    struct ncclChannelPeer* peer = channel->peers+r;
    for (int b=0; b<NCCL_MAX_CONNS; b++) {
      if (peer->recv[b].transportComm) NCCLCHECK(peer->recv[b].transportComm->free(peer->recv+b));
    }
  }

  return ncclSuccess;
}
