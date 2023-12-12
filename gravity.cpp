#include "gravity.h"
#include <stdlib.h>

int gravity(int NMass, Vector2D centerPos)
{
    //NBODY* pNbody = (NBODY*)malloc(sizeof(NBODY) * NMass);
    //InitNbody(pNbody, NMass, centerPos);
    //calAcceleration(pNbody, NMass);
    //printVector(pNbody, NMass);
    //free(pNbody);
    return 0;
}

void InitNbody(NBODY* pNbody, int NMass, Vector2D centerPos)
{
    for (int i = 0; i < NMass; i++)
    {
        int m = 100;
        int x = rand() % (int)centerPos.x;
        int y = rand() % (int)centerPos.y;
        int vx = rand() % 5 - 2;
        int vy = rand() % 5 - 2;
        Vector2D r(x, y), v(vx, vy), a(0,0);
        *(pNbody + i) = { m, r, v, a };
    }
}

void calAcceleration(NBODY* pNbody, int NMass)
{
    for (int i = 0; i < NMass; i++)
    {
        (pNbody + i)->fAcceleration.reset();
    }
    for (int i = 0; i < NMass; i++)
    {
        for (int j = 0; j < NMass; j++)
        {
            if (i != j)
            {
                Vector2D r = (pNbody + i)->fPosition - (pNbody + j)->fPosition;
                double r_length = r.length();
                if (r_length > NEAR_ZERO)
                {
                    (pNbody + i)->fAcceleration +=  -G_CONST * (pNbody + j)->nMass / (r_length * r_length * r_length) * r;
                }
                else
                {
                    (pNbody + i)->fAcceleration += Vector2D(0.,0.);
                }
                //printf("r = %f, a = %f\n", r_length, (pNbody + i)->fAcceleration.length());
            }
            else
            {
                (pNbody + i)->fAcceleration += Vector2D(0.,0.);
            }
        }
    }
}

void calSpeed(NBODY* pNbody, int NMass, double dt)
{
    //int SpeedLimit = 10000;
    for (int i = 0; i < NMass; i++)
    {
        (pNbody + i)->fSpeed += (pNbody + i)->fAcceleration * dt;
        //if ((pNbody + i)->fSpeed.x > SpeedLimit || (pNbody + i)->fSpeed.x < -SpeedLimit)
        //{
        //    (pNbody + i)->fSpeed.x /= SpeedLimit;
        //}
        //if ((pNbody + i)->fSpeed.y > SpeedLimit || (pNbody + i)->fSpeed.y < -SpeedLimit)
        //{
        //    (pNbody + i)->fSpeed.y /= SpeedLimit;
        //}
    }
}

void calPosition(NBODY* pNbody, int NMass, double dt)
{
    for (int i = 0; i < NMass; i++)
    {
        (pNbody + i)->fPosition += (pNbody + i)->fSpeed * dt;
    }
}

void printVector(NBODY* nNbody, int NMass)
{
    for (int i = 0; i < NMass; i++)
    {
        printf("Mass[%d] :", i);
        (nNbody + i)->fPosition.Display();
        (nNbody + i)->fSpeed.Display();
        (nNbody + i)->fAcceleration.Display();
        printf("\n");
    }
}