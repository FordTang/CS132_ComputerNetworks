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

int connectcosts1[4] = { 1, 0, 1, 999 };

struct distance_table
{
  int costs[4][4];
} dt1;


/* students to write the following two routines, and maybe some others */


void sendUpdate1()
{
  connectcosts1[0] = dt1.costs[1][0];
  connectcosts1[1] = dt1.costs[1][1];
  connectcosts1[2] = dt1.costs[1][2];
  connectcosts1[3] = dt1.costs[1][3];

  struct rtpkt to0, to2;

  to0.sourceid = 1;
  to0.destid = 0;

  to2.sourceid = 1;
  to2.destid = 2;

  int i;

  for (i = 0; i < 4; ++i)
  {
  	to0.mincost[i] = connectcosts1[i];
  	to2.mincost[i] = connectcosts1[i];
  }

  tolayer2(to0);
  tolayer2(to2);
}


rtinit1()
{
  dt1.costs[1][0] = 1;
  dt1.costs[1][1] = 0;
  dt1.costs[1][2] = 1;
  dt1.costs[1][3] = 999;

  sendUpdate1();
}


rtupdate1(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
  int i;
  unsigned char update = 0;

  for (i = 0; i < 4; ++i)
  {
    if ((rcvdpkt->mincost[i] + dt1.costs[1][rcvdpkt->sourceid]) < dt1.costs[1][i])
    {
      dt1.costs[1][i] = rcvdpkt->mincost[i] + dt1.costs[1][rcvdpkt->sourceid];
      update = 1;
    }
  }

  if (1 == update)
    sendUpdate1();
}


printdt1(dtptr)
  struct distance_table *dtptr;

{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);
}


linkhandler1(linkid, newcost)
  int linkid, newcost;
{
}