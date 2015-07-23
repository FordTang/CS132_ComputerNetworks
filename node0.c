#include <stdio.h>

extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };

extern int TRACE;
extern int YES;
extern int NO;

int connectcosts0[4] = { 0, 1, 3, 7 };

struct distance_table
{
  int costs[4][4];
} dt0;


/* students to write the following two routines, and maybe some others */


void sendUpdate0()
{
  //printf("sendUpdate0\n");
  connectcosts0[0] = dt0.costs[0][0];
  connectcosts0[1] = dt0.costs[0][1];
  connectcosts0[2] = dt0.costs[0][2];
  connectcosts0[3] = dt0.costs[0][3];

  struct rtpkt to1, to2, to3;

  to1.sourceid = 0;
  to1.destid = 1;

  to2.sourceid = 0;
  to2.destid = 2;

  to3.sourceid = 0;
  to3.destid = 3;

  int i;

  for (i = 0; i < 4; ++i)
  {
	to1.mincost[i] = connectcosts0[i];
	to2.mincost[i] = connectcosts0[i];
	to3.mincost[i] = connectcosts0[i];
  }

  tolayer2(to1);
  tolayer2(to2);
  tolayer2(to3);
}


void rtinit0()
{
  //printf("rtinit0\n");

  dt0.costs[0][0] = 0;
  dt0.costs[0][1] = 1;
  dt0.costs[0][2] = 3;
  dt0.costs[0][3] = 7;

  sendUpdate0();
}


void rtupdate0(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
  int i;
  unsigned char update = 0;

  for (i = 0; i < 4; ++i)
  {
    if ((rcvdpkt->mincost[i] + dt0.costs[0][rcvdpkt->sourceid]) < dt0.costs[0][i])
    {
      dt0.costs[0][i] = rcvdpkt->mincost[i] + dt0.costs[0][rcvdpkt->sourceid];
      update = 1;
    }
  }

  if (1 == update)
    sendUpdate0();
}


printdt0(dtptr)
  struct distance_table *dtptr;
{
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}


linkhandler0(linkid, newcost)
  int linkid, newcost;
{
}