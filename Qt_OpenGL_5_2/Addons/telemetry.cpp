#include "telemetry.h"

Telemetry::Telemetry()
{
    lastUpdate = QDateTime::currentMSecsSinceEpoch();
    currentFPS = 0;
    lastFPS = 0;
}

void Telemetry::logic()
{
    int now = QDateTime::currentMSecsSinceEpoch();
    if(now - lastUpdate >= 1000)
    {
        lastUpdate = now;
        lastFPS = currentFPS;
        currentFPS = 0;
    }

    currentFPS++;
}

