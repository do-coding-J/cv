#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

#define FPS 30

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    auto prev_time = chrono::system_clock::now();

    VideoCapture camera(0, CAP_V4L2);
    Mat frame;

    // Set the camera properties
    camera.set(CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));

    namedWindow("frame", WINDOW_AUTOSIZE);

    if (!camera.isOpened())
    {
        cerr << "Camera open failed" << endl;
        return -1;
    }

    while (1)
    {
        auto current_time = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = current_time - prev_time;

        if (elapsed_seconds.count() >= 1.0 / FPS)
        {
            try
            {
                camera >> frame;
                if (frame.empty())
                {
                    cerr << "Captured empty frame" << endl;
                    break;
                }

                imshow("frame", frame);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }

            prev_time = current_time;
        }

        // Use 'q' to quit and 1ms delay to process the GUI events
        if (waitKey(1) == 'q')
            break;
    }

    camera.release();
    destroyAllWindows();
    return 0;
}
