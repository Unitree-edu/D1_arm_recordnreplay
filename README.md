# unitree_d1_demo_sdk

Custom SDK-based demo for Unitree D1 arm with teaching, recording, and playback support.

---

### 🔁 Logic Flow

1. **Unlock joints (teaching mode)**  
   Use `joint_disable_control` to disable torque and allow free drag of the arm.

2. **Record trajectory**  
   Move the D1 arm manually while running `record_joint_angles` to save joint states into `recorded_angles.csv`.

3. **Enable joints**  
   Use `joint_enable_control` to re-enable torque and prepare the arm for playback.

4. **Replay**  
   Run `replay_joint_angles` to execute the recorded trajectory frame-by-frame.

---

### 🛠 Build Instructions

Ensure you have Unitree SDK v2 installed.

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```
---


| Module                         | Purpose                                  |
| ------------------------------ | ---------------------------------------- |
| `record_joint_angles`          | Records joint angles at 10Hz into CSV    |
| `replay_joint_angles`          | Replays CSV with fixed timing            |
| `joint_disable_control`        | Disables joint torque (enter teaching)   |
| `joint_enable_control`         | Enables joint torque (prepare to replay) |
| `get_arm_joint_angle`          | Prints live joint angles to console      |
| `multiple_joint_angle_control` | Sets all joints in one command           |
| `arm_zero_control`             | Returns arm to calibrated zero pose      |

---

For reference and SDK details, visit:
https://support.unitree.com/home/zh/developer/D1Arm_services
