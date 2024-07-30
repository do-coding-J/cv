#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

#define FPS 30
#define WINDOW_NAME1 "empty"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    /*------------------------------------------------------------------------------------------*/
    VideoCapture camera(0, CAP_V4L2);

    // Set the camera properties
    camera.set(CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));
    camera.set(CAP_PROP_BUFFERSIZE, 1);
    camera.set(CAP_PROP_FPS, FPS);
    camera.set(CAP_PROP_FRAME_WIDTH, 1200);
    camera.set(CAP_PROP_FRAME_HEIGHT, 720);

    // namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);

    if (!camera.isOpened())
    {
        cerr << "Camera open failed" << endl;
        return -1;
    }

    while (1)
    {
        Mat frame;
        camera >> frame;

        /*------------------------------------------------------------------------------------------*/

        Mat hsv, color_mask, color_output;
        uint8_t lb, lg, lr, hb, hg, hr;
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        // remove white space
        // Mat white_mask, white_output;
        // lb = 0;
        // lg = 0;
        // lr = 0;
        // hb = 50;
        // hg = 255;
        // hr = 255;
        // inRange(hsv, Scalar(lb,lg,lr), Scalar(hb,hg,hr), white_mask);
        // bitwise_not(frame, white_output, white_mask);


        // color parse
        lb = 20;
        lg = 0;
        lr = 100;
        hb = 70;
        hg = 255;
        hr = 255;
        inRange(hsv, Scalar(lb,lg,lr), Scalar(hb,hg,hr), color_mask);
        bitwise_and(frame, frame, color_output, color_mask);

        /*------------------------------------------------------------------------------------------*/

        Mat gray, gray_median;
        vector<Vec3f> circles;
        cvtColor(color_output, gray, COLOR_BGR2GRAY);
        medianBlur(gray, gray_median, 5);
        HoughCircles(gray_median, circles, HOUGH_GRADIENT, 1, 100, 50, 30, 0, 100);

        for (size_t i = 0; i < circles.size(); i++)
        {
            Vec3i c = circles[i];
            Point center = Point(c[0], c[1]);
            // circle outline
            int radius = c[2];
            circle(frame, center, radius, Scalar(255, 0, 255), 3, LINE_AA);
        }

        imshow("WINDOW_NAME1", frame);
        // imshow("WINDOW_NAME2", white_output);
        // imshow("WINDOW_NAME3", white_mask);

        // Use 'q' to quit and 1ms delay to process the GUI events
        if (waitKey(1) == 'q')
            break;
    }

    camera.release();
    destroyAllWindows();
    return 0;
}
