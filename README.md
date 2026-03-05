# How to assemble Lerobot
- https://wiki.seeedstudio.com/lerobot_so100m_new/#introduction
LeRobot SO-ARM101 Robotic Arm - Assembly and Setup Guide
- https://www.youtube.com/watch?v=70GuJf2jbYk
- https://huggingface.co/docs/lerobot/installation
- https://github.com/huggingface/lerobot
- https://github.com/Kotakku/FT_SCServo_Debug_Qt


# Install python3.10 and Lerobot
Install the dependency packages
```
sudo apt update
sudo apt install software-properties-common
sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt install python3.10 python3.10-dev python3.10-venv
sudo apt install ffmpeg
```

Setup the lerobot-env
```
python3 -m venv lerobot-env
source lerobot-env/bin/activate
```

Install lerobot
```
pip install lerobot
lerobot-info
```

Install scservo-sdk
```
#pip install scservo-sdk
#sudo apt install build-essential python3-dev
#pip install evdev

pip install 'lerobot[all]'          # All available features
pip install 'lerobot[aloha,pusht]'  # Specific features (Aloha & Pusht)
pip install 'lerobot[feetech]'      # Feetech motor support
```

# How to Calibrate
- https://www.youtube.com/watch?v=mQ7O73dEDcU
- Calibrate leader
```
lerobot-calibrate --teleop.type=so101_leader --teleop.port=/dev/ttyACM0 --teleop.id=leader
```
- Calibrate follower
```
lerobot-calibrate --robot.type=so101_follower --robot.port=/dev/ttyACM1 --robot.id=follower
```
- Teleoperate 
```
lerobot-teleoperate --robot.type=so101_follower --robot.port=/dev/ttyACM1 --robot.id=follower --teleop.type=so101_leader --teleop.port=/dev/ttyACM0 --teleop.id=leader
```
```
--robot.p_coefficient=8 (Lower = smoother, less responsive; Higher = more responsive, potentially jittery)
--robot.d_coefficient=16 (Lower = less dampening; Higher = more dampening but can cause oscillations)
default values: p_coefficient=8, i_coefficient=0, d_coefficient=20
```

# Error to access ttyACM0
```
sudo usermod -aG dialout $USER
newgrp dialout
```

# Recording 
- https://www.youtube.com/watch?v=-tkEMLOLEwo
- recording
```
lerobot-record --robot.type=so101_follower --robot.port=/dev/ttyACM1 --robot.id=follower --teleop.type=so101_leader --teleop.port=/dev/ttyACM0 --teleop.id=leader --display_data=true --dataset.reset_time_s=5 --dataset.push_to_hub=false --dataset.repo_id=local/pick2 --dataset.num_episodes=1 --dataset.single_task="Place the blue cube in the orange bowl."
```
- recording with camera
```
lerobot-record --robot.type=so101_follower --robot.port=/dev/ttyACM1 --robot.id=follower --robot.cameras="{ front: {type: opencv, index_or_path: 0, width: 1920, height: 1080, fps: 30}}" --teleop.type=so101_leader --teleop.port=/dev/ttyACM0 --teleop.id=leader --display_data=true --dataset.reset_time_s=5 --dataset.push_to_hub=false --dataset.repo_id=local/pick2 --dataset.num_episodes=1 --dataset.single_task="Place the blue cube in the orange bowl."
```
other option
```
#--resume true
#--dataset.root=/users/ronanmcgovern/.cache/hugingface/lerobot/Trelis/S0-101-ACT-test

```
# Replay
```
lerobot-replay --robot.type=so101_follower --robot.port=/dev/ttyACM1 --robot.id=follower --dataset.repo_id=local/pick2 --dataset.episode=0
```

# Training
```
lerobot-train --dataset.repo_id=local/pick_and_place_red_cube --policy.type=act --output_dir=outputs/train/local/pick_and_place_red_cube --job_name=act_so101_test --policy.device=cuda --wandb.enable=false --policy.repo_id=local/pick_and_place_policy --batch_size=2 --num_worker=0
```
```
INFO 2026-03-05 15:23:32 ot_train.py:195 {'batch_size': 2,
 'checkpoint_path': None,
 'dataset': {'episodes': None,
             'image_transforms': {'enable': False,
                                  'max_num_transforms': 3,
                                  'random_order': False,
                                  'tfs': {'affine': {'kwargs': {'degrees': [-5.0,
                                                                            5.0],
                                                                'translate': [0.05,
                                                                              0.05]},
                                                     'type': 'RandomAffine',
                                                     'weight': 1.0},
                                          'brightness': {'kwargs': {'brightness': [0.8,
                                                                                   1.2]},
                                                         'type': 'ColorJitter',
                                                         'weight': 1.0},
                                          'contrast': {'kwargs': {'contrast': [0.8,
                                                                               1.2]},
                                                       'type': 'ColorJitter',
                                                       'weight': 1.0},
                                          'hue': {'kwargs': {'hue': [-0.05,
                                                                     0.05]},
                                                  'type': 'ColorJitter',
                                                  'weight': 1.0},
                                          'saturation': {'kwargs': {'saturation': [0.5,
                                                                                   1.5]},
                                                         'type': 'ColorJitter',
                                                         'weight': 1.0},
                                          'sharpness': {'kwargs': {'sharpness': [0.5,
                                                                                 1.5]},
                                                        'type': 'SharpnessJitter',
                                                        'weight': 1.0}}},
             'repo_id': 'local/pick_and_place_red_cube',
             'revision': None,
             'root': None,
             'streaming': False,
             'use_imagenet_stats': True,
             'video_backend': 'torchcodec'},
 'env': None,
 'eval': {'batch_size': 50, 'n_episodes': 50, 'use_async_envs': False},
 'eval_freq': 20000,
 'job_name': 'act_so101_test',
 'log_freq': 200,
 'num_workers': 0,
 'optimizer': {'betas': [0.9, 0.999],
               'eps': 1e-08,
               'grad_clip_norm': 10.0,
               'lr': 1e-05,
               'type': 'adamw',
               'weight_decay': 0.0001},
 'output_dir': 'outputs/train/local/pick_and_place_red_cube',
 'peft': None,
 'policy': {'chunk_size': 100,
            'device': 'cpu',
            'dim_feedforward': 3200,
            'dim_model': 512,
            'dropout': 0.1,
            'feedforward_activation': 'relu',
            'input_features': {},
            'kl_weight': 10.0,
            'latent_dim': 32,
            'license': None,
            'n_action_steps': 100,
            'n_decoder_layers': 1,
            'n_encoder_layers': 4,
            'n_heads': 8,
            'n_obs_steps': 1,
            'n_vae_encoder_layers': 4,
            'normalization_mapping': {'ACTION': <NormalizationMode.MEAN_STD: 'MEAN_STD'>,
                                      'STATE': <NormalizationMode.MEAN_STD: 'MEAN_STD'>,
                                      'VISUAL': <NormalizationMode.MEAN_STD: 'MEAN_STD'>},
            'optimizer_lr': 1e-05,
            'optimizer_lr_backbone': 1e-05,
            'optimizer_weight_decay': 0.0001,
            'output_features': {},
            'pre_norm': False,
            'pretrained_backbone_weights': 'ResNet18_Weights.IMAGENET1K_V1',
            'pretrained_path': None,
            'private': None,
            'push_to_hub': True,
            'replace_final_stride_with_dilation': False,
            'repo_id': 'local/pick_and_place_policy',
            'tags': None,
            'temporal_ensemble_coeff': None,
            'type': 'act',
            'use_amp': False,
            'use_peft': False,
            'use_vae': True,
            'vision_backbone': 'resnet18'},
 'rabc_epsilon': 1e-06,
 'rabc_head_mode': 'sparse',
 'rabc_kappa': 0.01,
 'rabc_progress_path': None,
 'rename_map': {},
 'resume': False,
 'save_checkpoint': True,
 'save_freq': 20000,
 'scheduler': None,
 'seed': 1000,
 'steps': 100000,
 'tolerance_s': 0.0001,
 'use_policy_training_preset': True,
 'use_rabc': False,
 'wandb': {'disable_artifact': False,
           'enable': False,
           'entity': None,
           'mode': None,
           'notes': None,
           'project': 'lerobot',
           'run_id': None}}
INFO 2026-03-05 15:23:32 ot_train.py:203 Logs will be saved locally.
INFO 2026-03-05 15:23:32 ot_train.py:215 Creating dataset
INFO 2026-03-05 15:23:33 ot_train.py:233 Creating policy
INFO 2026-03-05 15:23:34 ot_train.py:288 Creating optimizer and scheduler
INFO 2026-03-05 15:23:34 ot_train.py:323 Output dir: outputs/train/local/pick_and_place_red_cube
INFO 2026-03-05 15:23:34 ot_train.py:330 cfg.steps=100000 (100K)
INFO 2026-03-05 15:23:34 ot_train.py:331 dataset.num_frames=912 (912)
INFO 2026-03-05 15:23:34 ot_train.py:332 dataset.num_episodes=5
INFO 2026-03-05 15:23:34 ot_train.py:335 Effective batch size: 2 x 1 = 2
INFO 2026-03-05 15:23:34 ot_train.py:336 num_learnable_params=51597190 (52M)
INFO 2026-03-05 15:23:34 ot_train.py:337 num_total_params=51597190 (52M)
INFO 2026-03-05 15:23:34 ot_train.py:393 Start offline training on a fixed dataset, with effective batch size: 2
```
Optimize Training Speed

1. Reduce Training Steps (The "Fast-Track")

Your current config is set to steps=100000. For a small local dataset of 5 episodes (912 frames), 100k steps is massive over-optimization.

    Optimization: Set --steps=5000 or even --steps=2000.

    Why: With only 5 episodes, the model will likely "memorize" the data (overfit) very quickly. You’ll see if it’s working much sooner.

2. Optimize the ACT Architecture

ACT is a "heavy" policy because of its Transformer layers. You can make it "skinnier" to speed up the math:

    Reduce Layers: Set --policy.n_encoder_layers=2 (down from 4) and --policy.n_vae_encoder_layers=2.

    Reduce Hidden Dim: Set --policy.dim_model=256 (down from 512).

    Why: This significantly reduces the number of matrix multiplications the CPU has to perform every iteration.

3. Increase the Learning Rate

If you reduce the number of steps, you need the model to learn faster.

    Optimization: Set --optimizer.lr=1e-4 (up from 1e-5).

    Why: A higher learning rate allows the weights to converge in fewer iterations, though it can be less stable.

4. Disable Image Augmentation

Your config shows image_transforms are enabled (RandomAffine, ColorJitter, etc.).

    Optimization: Set --dataset.image_transforms.enable=false.

    Why: Calculating rotations and color shifts on every batch is a heavy CPU task. For a quick test, skip it.

```
lerobot-train --dataset.repo_id=local/pick_and_place_red_cube --policy.type=act --output_dir=outputs/train/local/pick_and_place_red_cube --job_name=act_so101_test --policy.device=cpu --wandb.enable=false --policy.repo_id=local/pick_and_place_policy --batch_size=2 --num_worker=0 --steps=2000 --policy.n_encoder_layers=2 --policy.n_vae_encoder_layers=2 --policy.dim_model=256 --optimizer.lr=1e-4 --dataset.image_transforms.enable=false 

```
huggingface-cli upload ${HF_USER}/S0-101-ACT-test output/train/acct_test/checkpoints/last/pretrained_model
```




