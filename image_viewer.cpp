#include <opencv2/opencv.hpp>
#include <iostream> 

int main(int argc, char** argv){

    // Check that there are 2 arguments
    if(argc < 2){
        std::cout << "Usage: " << argv[0] << "<image_path>\n"; 
        return 0; 
    }

    // Read Image
    cv::Mat image = cv::imread(argv[1], cv::IMREAD_COLOR); 

    // Check if iamge is empty 
    if(image.empty()){
        std::cerr << "Error: Could not find or open the image\n";
        return -1;
    }


    // Show the image in a window
    cv::imshow("My Image", image);

    // Wait for any key press before closing
    cv::waitKey(0);

    return 0; 
}