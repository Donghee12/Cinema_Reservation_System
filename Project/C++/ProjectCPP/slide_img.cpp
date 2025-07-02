#include "slide_img.h"

void fadeTransition(const Mat& img1, const Mat& img2, int steps, int delay) {
    Mat blended;
    for (int i = 0; i <= steps; i++) {
        double alpha = (double)i / steps;
        double beta = 1.0 - alpha;
        addWeighted(img1, beta, img2, alpha, 0.0, blended);
        imshow("Slideshow", blended);
        if (waitKey(delay) == 27) return;  //Á¾·á
    }
}

void poster() {
    vector<string> imagePaths = {
        "1.jpg", "2.jpg", "3.jpg", "4.jpg", "5.jpg"
    };

    vector<Mat> images;
    for (const string& path : imagePaths) {
        Mat img = imread(path);
        if (img.empty()) {
            cerr << "Error: Cannot load " << path << endl;
            break;
        }
        images.push_back(img);
    }

    namedWindow("Slideshow", WINDOW_AUTOSIZE);

    int index = 0;
    while (true) {
        Mat currentImage = images[index];
        Mat nextImage = images[(index + 1) % images.size()];

        imshow("Slideshow", currentImage);
        if (waitKey(2000) == 27) break; 

        fadeTransition(currentImage, nextImage);

        index = (index + 1) % images.size();
    }

    destroyAllWindows();
}