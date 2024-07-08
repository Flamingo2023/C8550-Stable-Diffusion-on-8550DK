#include "prompt_solver.h"
#include "diffusion_solver.h"
#include "models/DecoderModel.h"

#include "cxxopts.hpp"
#include <cstdlib>
#include <time.h>
#include <iostream>

static PromptSolver prompt_solver;
static DiffusionSolver diffusion_solver;
static DecoderModel decode_solver;

int StableDiffusion_init(std::string path) {
    if (prompt_solver.load(path) < 0) {
        printf("[ERROR] prompt_solver load failed!\n");
        return -1;
    }

    if (diffusion_solver.load(path) < 0) {
        printf("[ERROR] diffusion_solver load failed!\n");
        return -1;
    }

    if (decode_solver.load(path) < 0) {
        printf("[ERROR] decode_solver load failed!\n");
        return -1;
    }
    return 0;
}

int StableDiffusion_txt2imgProcess(int step, int seed, int width, int height, std::string positivePromptEn, std::string negativePromptEn, std::string output) {
    std::string positive_prompt_en = positivePromptEn;
    std::string negative_prompt_en = negativePromptEn;
    std::string default_positive_prompt_en = "mini hamburgers shaped like the faces of cats, in the style of makoto shinkai, hergé, party kei, sculpted, naoto hattori, exquisite detailing";
    diffusion_solver.set_latent_size(height / 8, width / 8);
    decode_solver.set_latent_size(height / 8, width / 8);
    cv::Mat cond, uncond;
    if (prompt_solver.get_conditioning(positive_prompt_en, default_positive_prompt_en, cond) < 0) {
        printf("[ERROR] prompt_solver positive prompt inference failed!\n");
        return -1;
    }
    if (prompt_solver.get_conditioning(negative_prompt_en, "", uncond) < 0) {
        printf("[ERROR] prompt_solver negative prompt inference failed!\n");
        return -1;
    }
    cv::Mat sample;
    if (diffusion_solver.sampler_txt2img(seed, step, cond, uncond, sample) < 0) {
        printf("[ERROR] diffusion_solver inference failed!\n");
        return -1;
    }
    cv::Mat x_samples_ddim;
    if (decode_solver.decode(sample, x_samples_ddim) < 0) {
        printf("[ERROR] decode_solver inference failed!\n");
        return -1;
    }
    cv::cvtColor(x_samples_ddim, x_samples_ddim, cv::COLOR_BGR2RGB);
    cv::imwrite(output, x_samples_ddim);
    return 0;
}

int StableDiffusion_release() {
    if (prompt_solver.unload() < 0)
        return -1;
    if (diffusion_solver.unload() < 0)
        return -1;
    if (decode_solver.unload() < 0)
        return -1;
    return 0;
}

int main(int argc, char** argv) {
    time_t t;
    srand((unsigned) time(&t));
    
    cxxopts::Options options("./stablediffusion", "StableDiffusion-v1.0-qcom-qnn");
    options.add_options()
        ("e,epoch", "epoch", cxxopts::value<int>()->default_value("20"))
        ("s,seed", "seed", cxxopts::value<int>()->default_value("-1"))
        // ("w,width", "width", cxxopts::value<int>()->default_value("512"))
        // ("h,height", "height", cxxopts::value<int>()->default_value("512"))
        ("p,prompt", "positive prompt", cxxopts::value<std::string>()->default_value("3 corgi dogs running on grass field"))
        ("n,nprompt", "negetive prompt", cxxopts::value<std::string>()->default_value("lowres, bad anatomy, text, error, extra digit, fewer digits, cropped, worst quality, low quality, normal quality, jpeg artifacts,signature, watermark, username, blurry, artist name"))
        ("o,output", "output file", cxxopts::value<std::string>()->default_value("output.jpg"))
        ("help", "Print usage")
    ;
    auto result = options.parse(argc, argv);
    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    int epoch  = result["epoch"].as<int>();
    int seed   = result["seed"].as<int>();
    // int width  = result["width"].as<int>();
    // int height = result["height"].as<int>();
    std::string pos_prompt = result["prompt"].as<std::string>();
    std::string neg_prompt = result["nprompt"].as<std::string>();
    std::string output     = result["output"].as<std::string>();
    if (seed   <= 0                ) seed   = rand();
    if (epoch  <= 0 || epoch  > 20 ) epoch  = 20;
    // if (width  <= 0 || width  > 512) width  = 512;
    // if (height <= 0 || height > 512) height = 512;
    StableDiffusion_init("./");
    StableDiffusion_txt2imgProcess(epoch, seed, 512, 512, pos_prompt, neg_prompt, output);
    StableDiffusion_release();
    return 0;
}