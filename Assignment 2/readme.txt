/************* DISK ON FILE BLOCK DEVICE DRIVER *****************/

Steps to see output

1) Open the folder which contains the main.c and Makefile

2) Open terminal and type the command :  make 

3) Type the command :  sudo insmod main.ko

4) To check whether main.ko is loaded or not we have can check message log by using the command : dmesg

5) Check the partitions using the any one of the commands
    
    . sudo fdisk -l /dev/dof     //This gives complete info about total device size and each sector size and no of primary and extended partitions created 
                  (or) 
    . ls -l /dev/dof*     // This gives only the no of primary and extended partitions created and its permissions

6) To get details about the block using diskdump utility (dd) use the following commands
    
    . dd if=/dev/dof of=dof

7) Inorder to write data into the block device use the following steps
   
   . First Convert the permissions using the command : sudo chmod 777 /dev/dof1
   
   . To write data into the block use the command : cat > /dev/dof1
   . Now write the data into the block " Hi this is sainadh reddy "

   . To display the data written in the block use the command : xxd /dev/dof1 | less
   
8) To remove the block driver use the command : sudo rmmod main.ko

/********************* END ************************/
             

