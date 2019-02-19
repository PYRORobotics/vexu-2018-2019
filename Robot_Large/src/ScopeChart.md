# Scope Chart

## main()
Yes, the actual main() running deep in the heart of the V5 brain's PROS archetecture. This scope chart _(hypothesized)_ is based on PROS GitHub (pros/src/system/), which tasks are preceded by (%) and static tasks or functions are bracketed.
```
int main()
{
  [%system_deamon] -> Creates competition tasks and runs FMS logic
  {
    [%_initialize_task] -> Runs initialize() only once (upon boot).

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
