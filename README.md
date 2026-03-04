How to assemble lerobot

- https://www.youtube.com/watch?v=70GuJf2jbYk

- https://huggingface.co/docs/lerobot/installation

- https://github.com/huggingface/lerobot

- https://github.com/Kotakku/FT_SCServo_Debug_Qt


install python3.10
------------------
```
sudo apt install python3-dev python3-venv
python3 -m venv lerobot-py310

source lerobot-py310/bin/activate

sudo apt install software-properties-common
sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt install python3.10 python3.10-dev python3.10-venv
pip install lerobot
lerobot-info


sudo apt update
sudo apt install build-essential python3-dev
pip install evdev
```

Install scservo-sdk
-------------------
```
#pip install scservo-sdk
pip install 'lerobot[all]'          # All available features
pip install 'lerobot[aloha,pusht]'  # Specific features (Aloha & Pusht)
pip install 'lerobot[feetech]'      # Feetech motor support
```
calibrate
---------
https://www.youtube.com/watch?v=mQ7O73dEDcU
```
python -m lerobot.calibrate --teleop.type=so101_leader --teleop.port=/dev/ttyACM0 --teleop.id=leader

python -m lerobot.calibrate --teleop.type=so101_follower --teleop.port=/dev/ttyACM1 --teleop.id=follower


python -m lerobot.teleoperate --robot.type=so101_follower --robot.port=/dev/ttyACM1 --robot.id=follower 
--teleop.type=so101_leader --teleop.port=/dev/ttyACM0 --teleop.id=leader
```

--robot.p_coefficient=8 (Lower = smoother, less responsive; Higher = more responsive, potentially jittery)
--robot.d_coefficient=16 (Lower = less dampening; Higher = more dampening but can cause oscillations)
default values: p_coefficient=8, i_coefficient=0, d_coefficient=20

error to access ttyACM0
-----------------------
```
sudo usermod -aG dialout $USER
newgrp dialout
```
training and recording (https://www.youtube.com/watch?v=-tkEMLOLEwo)
----------------------
```
python -m lerobot.record 
--robot.type=so101_follower 
--robot.port=/dev/ttyACM1 
--robot.id=follower 
--robot.camera="{ wrist: {type: openCV, index_or_path: 0, width: 640, height: 480, fps: 30}, front: {type: openCV, index_or_path: 1, width: 640, height: 480, fps: 30}}"
--teleop.type=so101_leader 
--teleop.port=/dev/ttyACM0 
--teleop.id=leader
--display_data=true
--dataset.repo_id=${HF_USER}/S0-101-ACT-test
--dataset.num_episodes=2
--dataset.single_task="Place the blue cube in the orange bowl."
--dataset.reset_time_s=5
#--resume true
#--dataset.root=/users/ronanmcgovern/.cache/hugingface/lerobot/Trelis/S0-101-ACT-test
```
```
python -m lerobot.replay 
--robot.type=so101_follower 
--robot.port=/dev/ttyACM1 
--robot.id=follower 
--dataset.repo_id=${HF_USER}/S0-101-ACT-test
--dataset.episode=0
```
```
python lerobot/scripts/train.py 
--dataset.repo_id=${HF_USER}/S0-101-ACT-test
--policy.type=act
--output_dir=outputs/train/act_test
--job_name=act_test
--policy.device=cpu
#--policy.device=cuda
--wandb.enable=true
--dataset.image_transforms.enable=false
```
```
huggingface-cli upload ${HF_USER}/S0-101-ACT-test output/train/acct_test/checkpoints/last/pretrained_model
```




