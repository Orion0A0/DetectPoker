#include <filesystem>

#include "Card_Identifier.h"

#define POKER_FOLDER "/poker_model/"
#define CONFIG_FILE "poker.cfg"
#define WEIGHTS_FILE "poker_best.weights"
#define NAMES_FILE "poker.names"

#define DEFAULT_CAMERA 0
#define FIND_NUM_POKER 5
#define DISPLAY_SCREEN "camera"
#define RESULT_WINDOW "ResultWindow"
int main(int argc, char** argv)
{
    // built inside build directory, so need to go back one step
    std::string currDir = std::filesystem::current_path().parent_path().string();

    // config to prevent unexpect name format that will break the lookup table
    DarkHelp::Config cfg (currDir + POKER_FOLDER + CONFIG_FILE, currDir + POKER_FOLDER +  WEIGHTS_FILE, currDir + POKER_FOLDER + NAMES_FILE);
    cfg.names_include_percentage = false;
    cfg.include_all_names = false;

    DarkHelp::NN nn {cfg};
    cv::Mat frame;
    cv::VideoCapture camera {DEFAULT_CAMERA, cv::CAP_V4L2};
    cv::namedWindow(DISPLAY_SCREEN);

    if (!camera.isOpened())
    {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    std::cout << "Start reading" << std::endl;

    int pokerFound = 0;
    int timeTaken = 0;
    while (pokerFound < FIND_NUM_POKER)
    {
        camera.read(frame);
        if (frame.empty())
        {
            std::cerr << "ERROR! Read a blank frame\n";
            break;
        }

        nn.predict(frame);
        cv::imshow(DISPLAY_SCREEN, frame);

        if (Card_Identifier::processData(nn.prediction_results))
        {
            std::cout << "Found Card: " << Card_Identifier::getLastDetectedCard().to_string() << std::endl;
            cv::imshow(RESULT_WINDOW,nn.annotate());
            std::cout << "Press anything to continue" << std::endl;
            cv::waitKey(0);
            cv::destroyWindow(RESULT_WINDOW);
            pokerFound++;
        } else
        {
            std::cout << "Please adjust card's position" << timeTaken++ << std::endl;
        }
        if (cv::waitKey(25) == 'q')
            break;
    }

    cv::destroyAllWindows();
    return 0;
}

