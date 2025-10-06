#include <iostream>
#include <fcntl.h>       // for open()
#include <unistd.h>      // for close(), dup2()
#include <sys/ioctl.h>   // for ioctl()
#include <linux/fb.h>    // for framebuffer structs and constants
#include <errno.h>       // for errno
#include <string.h>      // for strerror()
#include <cstdlib>       // for exit()

using namespace std;

int main() {
    int selection;
    // Redirect standard error to Screen.log
    int logFd = open("Screen.log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (logFd < 0) {
        cerr << "Failed to open Screen.log: " << strerror(errno) << endl;
        return 1;
    }
    dup2(logFd, STDERR_FILENO);
    close(logFd);

    // Open framebuffer device
    int fbFd = open("/dev/fb0", O_RDONLY | O_NONBLOCK);
    if (fbFd < 0) {
        cerr << "Error opening /dev/fb0: " << strerror(errno) << endl;
        return 1;
    }

    do {
        cout << "\nChoose from the following:" << endl;
        cout << "1. Fixed Screen Info" << endl;
        cout << "2. Variable Screen Info" << endl;
        cout << "0. Exit" << endl << endl;
        cin >> selection;

        switch (selection) {
            case 1: {
                struct fb_fix_screeninfo fixInfo;
                int ret = ioctl(fbFd, FBIOGET_FSCREENINFO, &fixInfo);
                if (ret < 0) {
                    cerr << "ioctl FBIOGET_FSCREENINFO failed: "
                         << strerror(errno) << endl;
                    break;
                }

                cout << "\n=== Fixed Screen Info ===\n";
                cout << "Visual Type: " << fixInfo.visual << endl;
                cout << "Accelerator:  " << fixInfo.accel << endl;
                cout << "Capabilities: " << fixInfo.capabilities << endl;
		//visual type: 2
		//accelerator: 0
		//capabilities: 0
                break;
            }

            case 2: {
                struct fb_var_screeninfo varInfo;
                int ret = ioctl(fbFd, FBIOGET_VSCREENINFO, &varInfo);
                if (ret < 0) {
                    cerr << "ioctl FBIOGET_VSCREENINFO failed: "
                         << strerror(errno) << endl;
                    break;
                }

                cout << "\n=== Variable Screen Info ===\n";
                cout << "X Resolution: " << varInfo.xres << endl;
                cout << "Y Resolution: " << varInfo.yres << endl;
                cout << "Bits Per Pixel: " << varInfo.bits_per_pixel << endl;
		//X resolution: 1280
		//Y resolution: 800
		//Bits per pixel: 32
                break;
            }

            case 0:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice, try again.\n";
                break;
        }
    } while (selection != 0);

    close(fbFd);
    return 0;
}
