#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>

int main() {

    char cwd[PATH_MAX];
    if(getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("dir : %s", cwd);
    }

    cv::Mat image = cv::imread("./img/example.jpg"); // 이미지 파일을 읽어옴

    if (image.empty()) {
        std::cerr << "Could not read the image" << std::endl;
        return 1;
    }

    cv::imshow("Display window", image); // 이미지를 화면에 표시
    int k = cv::waitKey(0); // 키 입력 대기

    if (k == 's') {
        cv::imwrite("output.jpg", image); // 키 입력이 's'이면 이미지를 저장
    }

    return 0;
}
