/*
 *  ioctl.c - the process to use ioctl's to control the kernel module
 *
 *  Until now we could have used cat for input and output.  But now
 *  we need to do ioctl's, which require writing our own process.
 */

/*
 * device specifics, such as ioctl numbers and the
 * major device file.
 */
#include "ASSIGN.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>              /* open */
#include <unistd.h>             /* exit */
#include <sys/ioctl.h>          /* ioctl */


/*
 * Functions for the ioctl calls
 */
u_int16_t buffer;
int count;
///////////////////// MPU9255 Sensor - GYROSCOPE IOCTL FUNCTION CALLS  //////////////////
int ioctl_x_pitch_gyro (int file_desc, char *message)              //Function that reads the Pitch of Gyroscope
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_X_PITCH_GYRO, message);   //ioctl function call with request code  IOCTL_X_PITCH_GYRO
    if (ret_val == 0) {
        printf("Gyroscope failed to sense PITCH:%d\n", ret_val);
        exit(-1);
    }
    else
    printf("Pitch obtained from Gyroscope is : \n");
    return 0;
}

int ioctl_y_yaw_gyro(int file_desc, char *message)              //Function that reads the Yaw of Gyroscope
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_Y_YAW_GYRO, message);      //ioctl function call with request code  IOCTL_Y_YAW_GYRO

    if (ret_val ==  0) {
        printf("Gyroscope failed to sense YAW:%d\n", ret_val);
        exit(-1);
    }
    else
    printf("Yaw obtained from Gyroscope is : \n");
    return 0;
}

int ioctl_z_roll_gyro(int file_desc, char *message)           //Function that reads the Roll of Gyroscope
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_Z_ROLL_GYRO, message);   //ioctl function call with request code  IOCTL_Z_ROLL_GYRO

    if (ret_val ==  0) {
        printf("Gyroscope failed to sense ROLL:%d\n", ret_val);
        exit(-1);
    }
    else
    printf("Roll obtained from Gyroscope is : \n");
    return 0;
}


///////////////////// MPU9255 Sensor - ACCELEROMETER IOCTL FUNCTION CALLS  //////////////////
int ioctl_x_fb_accelero(int file_desc, char *message)               //Function that reads the Forward or Backward acceleration obtained from accelerometer
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_X_FB_ACCELERO, message);       //ioctl function call with request code  IOCTL_X_FB_ACCELERO

    if (ret_val ==  0) {
        printf("Accelerometer failed to sense Forward or Backward acceleration:%d\n", ret_val);
        exit(-1);
    }
    else
    printf("Forward or Backward acceleration obtained from Accelerometer is : \n");
    return 0;
}

int ioctl_y_lr_accelero(int file_desc, char *message)              //Function that reads the Left or Right acceleration obtained from accelerometer
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_Y_LR_ACCELERO, message);       //ioctl function call with request code  IOCTL_Y_LR_ACCELERO

    if (ret_val ==  0) {
        printf("Accelerometer failed to sense Left or Right acceleration:%d\n", ret_val);
        exit(-1);
    }
    else
    printf("Left or Right acceleration obtained from Accelerometer is : \n");
    return 0;
}

int ioctl_z_ud_accelero(int file_desc, char *message)              //Function that reads the Up or Down acceleration obtained from accelerometer
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_Z_UD_ACCELERO, message);      //ioctl function call with request code  IOCTL_Z_UD_ACCELERO

    if (ret_val ==  0) {
        printf("Accelerometer failed to sense Up or Down acceleration:%d\n", ret_val);
        exit(-1);
    }
    else
    printf("Up or Down acceleration obtained from Accelerometer is : \n");
    return 0;
}


///////////////////// MPU9255 Sensor - COMPASS/MAGNETOMETER IOCTL FUNCTION CALLS  //////////////////
int ioctl_x_dir_compass(int file_desc, char *message)              //Function that reads the X-direction obtained from Compass/Magnetometer
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_X_DIR_COMPASS, message);       //ioctl function call with request code  IOCTL_X_DIR_COMPASS

    if (ret_val ==  0) {
        printf("Compass failed to sense X-direction:%d\n", ret_val);
        exit(-1);
    }
    else
    printf("X-direction obtained from Compass/Magnetometer is : \n");
    return 0;
}

int ioctl_y_dir_compass(int file_desc, char *message)              //Function that reads the Y-direction obtained from Compass/Magnetometer
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_Y_DIR_COMPASS, message);      //ioctl function call with request code  IOCTL_Y_DIR_COMPASS

    if (ret_val ==  0) {
        printf("Compass failed to sense Y-direction:%d\n", ret_val);
        exit(-1);
    }
    else
    printf("Y-direction obtained from Compass/Magnetometer is : \n");
    return 0;
}

int ioctl_z_dir_compass(int file_desc, char *message)              //Function that reads the Z-direction obtained from Compass/Magnetometer
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_Z_DIR_COMPASS, message);     //ioctl function call with request code  IOCTL_Z_DIR_COMPASS

    if (ret_val ==  0) {
        printf("Compass failed to sense Z-direction:%d\n", ret_val);
        exit(-1);
    }
    else
    printf("Z-direction obtained from Compass/Magnetometer is : \n");
    return 0;
}

///////////////////// BMP290 Barometer Sensor - Barometer pressure  IOCTL FUNCTION CALL  //////////////////
int ioctl_pressure_baro(int file_desc, char *message)              //Function that reads the pressure obtained from Barometer
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_PRESSURE_BAROMETER, message);    //ioctl function call with request code  IOCTL_PRESSURE_BAROMETER

    if (ret_val ==  0) {
        printf("Barometer failed to sense pressure:%d\n", ret_val);   //fail indicator
        exit(-1);
    }
    else
    printf("Pressure obtained from Barometer is : \n");
    return 0;
}

/*
 * Main - Call the ioctl functions
 */
int main()
{
    int file_desc,select ;
   

    file_desc = open(DEVICE_FILE_NAME, 0);                   // opening the device node and returning the value to file_desc
    if (file_desc < 0) {
        printf("Can't open device file: %s\n", DEVICE_FILE_NAME);             //Display if permission is denied to open /dev/imu_char
        printf("Enter the following command in terminal and try previous steps :  sudo chmod 777 /dev/imu_char \n");  //alternate to get permission and continue the process
        
        exit(-1);
    }

    printf("Select the option to be displayed from the below options:   \n");
    printf("1. Pitch obtained from Gyroscope  \n2. Yaw obtained from Gyroscope \n3. Roll obtained from gyroscope \n");
    printf("4. Forward or Backward acceleration obtained from accelerometer  \n5. Left or Right acceleration obtained from accelerometer \n6. Up or Down acceleration obtained from accelerometer \n");
    printf("7. X-direction obtained from Compass  \n8. Y-direction obtained from Compass \n9. Z-direction obtained from Compass \n");
    printf("10. Pressure in pascals obtained from Barometer \n");
    scanf("%d",&select);                 //user selects which output he required from the options
     
     switch(select)                     //Calling the required ioctl function call as per the choice of user 
     {
          case 1: ioctl_x_pitch_gyro(file_desc,"1");
                  break;
          case 2: ioctl_y_yaw_gyro(file_desc,"2");
                  break;
          case 3: ioctl_z_roll_gyro(file_desc,"3");
                  break;
          case 4: ioctl_x_fb_accelero(file_desc,"4");
                  break;
          case 5: ioctl_y_lr_accelero(file_desc,"5");
                  break;
          case 6: ioctl_z_ud_accelero(file_desc,"6");
                  break;
          case 7: ioctl_x_dir_compass(file_desc,"7");
                  break;
          case 8: ioctl_y_dir_compass(file_desc,"8");
                  break;
          case 9: ioctl_z_dir_compass(file_desc,"9");
                  break;
          case 10: ioctl_pressure_baro(file_desc,"10");
                  break;
          default: printf("Choose proper option\n");
                  break;
     }  
    if(select<=10 && select>0)
    { 
       count = read(file_desc, &buffer, sizeof(buffer));            // storing the value in the buffer (where the driver sent is stored
       printf("%d\n", count);                                       // displaying the buffer value which is random value generated by the driver
    }
    close(file_desc);                                             // closing the device file
    return 0;
}
