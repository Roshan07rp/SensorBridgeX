# Interview Questions

## 1. Why character device?
It provides a controlled file-like interface between user space and the Linux driver.

## 2. What is kernel space?
The privileged execution environment where the Linux kernel and drivers operate.

## 3. What is user space?
The restricted environment where normal applications such as the C++ gateway run.

## 4. What is /dev/sensorbridge?
The device node exposed to user space for communicating with the driver.

## 5. What is file_operations?
A Linux kernel structure containing callbacks for device-file operations such as open, read, write and ioctl.

## 6. Why copy_to_user?
It safely transfers data from kernel memory to user-space memory.

## 7. Why ioctl?
For device-specific control/configuration operations that do not naturally fit read/write.

## 8. Why C for the driver?
Linux kernel and driver APIs are primarily C-based.

## 9. Why C++ for the gateway?
C++ provides convenient user-space abstraction while still allowing direct Linux system-call use.

## 10. How would you connect real hardware?
Use an appropriate interface such as I2C, SPI or GPIO and replace the simulator/hardware abstraction with the real sensor interface.
