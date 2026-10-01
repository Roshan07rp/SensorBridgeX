# Driver Design

The driver demonstrates:

- dynamic character-device number allocation
- `struct cdev`
- `struct file_operations`
- `open`
- `read`
- `write`
- `release`
- `unlocked_ioctl`
- `copy_to_user`
- `copy_from_user`
- mutex protection
- module init/exit

The driver creates `/dev/sensorbridge`.
