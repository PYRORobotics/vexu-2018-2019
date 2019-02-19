# Scope Chart

## main()
Yes, the actual main() running deep in the heart of the V5 brain's PROS archetecture. This scope chart _(hypothesized)_ shows PYRO's 2018-2019 VEX U robots' task interaction and is based on PROS GitHub (pros/src/system/), which tasks are preceded by (%) and static tasks or functions are bracketed.
```
int main()
{
  [%system_deamon] -> Creates competition tasks and runs FMS logic
  {
    [%_initialize_task] -> Runs initialize() only once (upon boot).
                                {
                                   %SerialTask -> Runs SerialReadTask(), which uses serialRead() to establish communications with the Raspberry Pi and get data packets. Because this task is run in a static parent task, it inherently acts as static.
                                   %UpdateTelemetryTask -> Runs UpdateTelemetry() to calculate a data-fused simple odometry using the IMU (Raspberry Pi) and the average motor rotations between the left and right middle motors' integrated motor encoders. Because this task is run in a static parent task, it inherently acts as static.
                                   %WaypointPIDTask -> Runs WaypointPID() to use the odometry telemetry information calculated in UpdateTelemetryTask to calculate robot point turn and drive distance setpoints, and runs a dual PID controller to first point turn to the desired Waypoint and then drive to the Waypoint's coordinates. Because this task is run in a static parent task, it inherently acts as static.
                                   %ScreenTask() -> [TODO: Not implemented yet] Runs ScreenUpdate() to control the PYRO GUI on the V5 brain's screen. Because this task is run in a static parent task, it inherently acts as static.
                                }

    while(1)
    {
      [%competition_task] =
                            [%_competition_initialize_task] -> Runs competition_initialize()
                            OR
                            [%_autonomous_task] -> Runs autonomous()
                            OR
                            [%_opcontrol_task] -> Runs  opcontrol()
                            OR
                            [%_disabled_task] -> Runs disabled().
    }
  }
}
```
