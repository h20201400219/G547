#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/ioctl.h>

#define MAJOR_NUM 100

#define IOCTL_X_PITCH_GYRO _IOWR(MAJOR_NUM, 0, char *)

#define IOCTL_Y_YAW_GYRO _IOWR(MAJOR_NUM, 1, char *)

#define IOCTL_Z_ROLL_GYRO _IOWR(MAJOR_NUM, 2, char *)

#define IOCTL_X_FB_ACCELERO _IOWR(MAJOR_NUM, 3, char *)

#define IOCTL_Y_LR_ACCELERO _IOWR(MAJOR_NUM, 4, char *)

#define IOCTL_Z_UD_ACCELERO _IOWR(MAJOR_NUM, 5, char *)

#define IOCTL_X_DIR_COMPASS _IOWR(MAJOR_NUM, 6, char *)

#define IOCTL_Y_DIR_COMPASS _IOWR(MAJOR_NUM, 7, char *)

#define IOCTL_Z_DIR_COMPASS _IOWR(MAJOR_NUM, 8, char *)

#define IOCTL_PRESSURE_BAROMETER _IOWR(MAJOR_NUM, 9, char *)

#define DEVICE_FILE_NAME "/dev/imu_char"

#endif
