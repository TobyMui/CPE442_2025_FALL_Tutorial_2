#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    std::cout << "Press esc or q to close the window! \n";

    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <video_path>" << std::endl;
        return -1;
    }

    const std::string kWin = "Grayscale Video";

    cv::VideoCapture cap(argv[1]);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return -1;
    }

    cv::namedWindow(kWin, cv::WINDOW_AUTOSIZE);

    cv::Mat frame, gray;
    while (true) {
        if (!cap.read(frame) || frame.empty()) {
            std::cout << "End of video." << std::endl;
            break;
        }

        // Manually convert to grayscale using CCIR 601 coefficients
        gray.create(frame.rows, frame.cols, CV_8UC1);
        for (int y = 0; y < frame.rows; y++) {
            for (int x = 0; x < frame.cols; x++) {
                cv::Vec3b color = frame.at<cv::Vec3b>(y, x);
                uchar B = color[0];
                uchar G = color[1];
                uchar R = color[2];

                // CCIR 601 formula
                uchar Y = static_cast<uchar>(
                    0.299 * R + 0.587 * G + 0.114 * B
                );

                gray.at<uchar>(y, x) = Y;
            }
        }

        // Show grayscale video
        cv::imshow(kWin, gray);

        // Handle keys and window events
        int key = cv::waitKey(25);
        if (key == 'q' || key == 27) { // quit on 'q' or ESC
            break;
        }
        if (cv::getWindowProperty(kWin, cv::WND_PROP_AUTOSIZE) < 0) {
            break; // window closed
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
