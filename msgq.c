#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//this is the structure of the message i'm sending to the queue
struct message
{
    long messagetype;
    char text[10];
}; 

int main()
{

    key_t key = 2222;
    int msqid = msgget(key, IPC_CREAT); //create a message queue with the key


    pid_t parentpid = getpid();
    pid_t childpid = fork(); //these are mostly unused for now
    if(childpid < 0) //fork failed
    {
        printf("fork failed\n");
        return 1;
    } else if(childpid == 0) //in child process
    {
        struct message sndmsg; //create a message to be send to the queue
        printf("input message\n"); 
        scanf("%s", sndmsg.text);  //get the messages text fro input
        printf("Sending message to queue: %s\n", sndmsg.text); 
        sndmsg.messagetype = 1; //set message type to 1
        if(msgsnd(msqid, &sndmsg, sizeof(sndmsg.text), 0) < 0 ) // no idea what the last parameter really means here. check if message send fails 
        {
            printf("error sending message\n");
        } else
        {
            printf("sent message with text: %s\n",sndmsg.text);
        }

        printf("child process\n");
    } else
    {
        wait(NULL); //wait until child process is done
        struct message rcvmsg; //create a message to recieve the test from the queue
        rcvmsg.messagetype = 1; //matching the message type here
        if(msgrcv(msqid, &rcvmsg, sizeof(rcvmsg.text), 1, 0) < 0) //again, no idea what the last parameter does here. Checking to see if message recieve fails.
        {
            printf("error recieving message\n");
        } else
        {
        printf("recieved message text : %s\n", rcvmsg.text);
        }
        printf("Parent process\n");
    }
    return 0;
}
