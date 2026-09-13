#include <filesystem>

#include <DarkHelp.hpp>
#include <opencv2/imgcodecs.hpp>

#define POKER_FOLDER "/poker_model/"
#define CONFIG_FILE "poker.cfg"
#define WEIGHTS_FILE "poker_best.weights"
#define NAMES_FILE "poker.names"

#define WIDTH 756
#define HEIGHT 1008
#define TEST_IMG "/home/orion/Downloads/ace.jpg"
#define TEST_VID "/home/orion/Downloads/vid.mp4"
int main(int argc, char** argv)
{
    // currentPath returns build directory, so travel one step upward

    std::string currDir = std::filesystem::current_path().parent_path().string();
    DarkHelp::Config cfg (currDir + POKER_FOLDER + CONFIG_FILE, currDir + POKER_FOLDER +  WEIGHTS_FILE, currDir + POKER_FOLDER + NAMES_FILE);
    cfg.names_include_percentage = true;
    cfg.annotation_auto_hide_labels = false;
    cfg.enable_tiles = false;
    cfg.combine_tile_predictions = true;

    DarkHelp::NN nn (cfg);

    // cv::VideoCapture video(TEST_VID);
    // cv::namedWindow("show", cv::WINDOW_NORMAL);
    // cv::resizeWindow("show", cv::Size(WIDTH, HEIGHT));
    // while (video.isOpened())
    // {
    //     cv::Mat frame;
    //     cv::Mat resized_img;
    //     video.read(frame);
    //     if (frame.empty())
    //         break;
    //     // cv::resize(frame, resized_img, cv::Size(WIDTH, HEIGHT));
    //     //
    //     // const auto result = nn.predict(resized_img);
    //     const auto result = nn.predict(frame);
    //     cv::Mat annotate = nn.annotate();
    //     cv::imshow("show", annotate);
    //     cv::waitKey(0);
    // }

    cv::Mat origin_img = cv::imread(TEST_IMG);
    cv::Mat resized_img;
    cv::resize(origin_img, resized_img, cv::Size(WIDTH, HEIGHT));
    auto result = nn.predict(resized_img);
    cv::Mat annotate = nn.annotate();
    cv::namedWindow("show", cv::WINDOW_NORMAL);
    cv::resizeWindow("show", cv::Size(2560, 1600));
    cv::imshow("show", annotate);
    cv::imwrite("poke.jpg", annotate);
    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}