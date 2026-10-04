# AeroRTOS (ARINC LIB)

AeroRTOS is a lightweight ARINC 653 RTOS framework.  
It demonstrates partitioned scheduling, process orchestration.

---

## Project Structure

```
Aerospace-OS/
├── CMakeLists.txt
├── config.yaml          # System definition (partitions, processes)
├── config.py            # Generator script
├── Runner/
│   ├── start_rtos.c           # Auto-generated runner
│   └── partitions.cmake # Auto-generated CMake fragment
├── RTOS/ARINC653/{Src,Inc}
```

---

## Workflow

1. **Define system in YAML**  
   Edit `config.yaml` to describe partitions and processes:
   ```yaml
   system:
     major_frame_ns: 100000000
     partitions:
       - name: Partition1
         duration_ns: 30000000
         offset_ns: 0
         processes:
           - name: Process1
             entry: task1
             period_ns: 100000000
             timecap_ns: 20000000
             priority: 10
       - name: Partition2
         duration_ns: 30000000
         offset_ns: 30000000
         processes:
           - name: Process1
             entry: task2
             period_ns: 100000000
             timecap_ns: 25000000
             priority: 9
       - name: Partition3
         duration_ns: 40000000
         offset_ns: 60000000
         processes:
           - name: Process1
             entry: task3
             period_ns: 100000000
             timecap_ns: 30000000
             priority: 8
   ```

2. **Generate code**  
   Run the generator:
   ```bash
   python config.py config.yaml .
   ```
   This creates:
   - `Runner/start_rtos.c` with system setup

3. **Build with CMake**  
   Configure and build:
   ```bash
   cmake -S . -B build
   cmake --build build
   ```

   The top‑level `CMakeLists.txt` includes `Runner/partitions.cmake` so the generated sources are compiled automatically.

---

## 🛠️ Key Components

- **RTOS/ARINC653**: Core scheduling, partition/process management
- **Runner/**: Auto‑generated entry point (`main.c`) and build fragment

---

## Example Run

After building, the executable will:
- Initialize 3 partitions (`Partition1`, `Partition2`, `Partition3`)
- Attach one process per partition (`task1`, `task2`, `task3`)
- Start each process and run the scheduler

Console output will look like:

```
task1 running in Partition1/Process1
task2 running in Partition2/Process1
task3 running in Partition3/Process1
```

---

## Notes

- Always regenerate after editing `config.yaml` (`python config.py config.yaml .`).
- The build is deterministic: no globbing, all sources/headers are listed in `Runner/partitions.cmake`.
- Extend `config.yaml` to add more partitions or processes — the generator handles them automatically.