#ifndef STABLEDIFFUSION_SCHEDULER_BASE_H
#define STABLEDIFFUSION_SCHEDULER_BASE_H

#include "utils/utils.h"


class scheduler_base {
public:
    virtual std::vector<float> set_timesteps(int num_inference_steps) = 0;

    virtual cv::Mat scale_model_input(cv::Mat &sample, int step_index) = 0;

    virtual cv::Mat step(int step_index, cv::Mat &sample_mat, cv::Mat &denoised, cv::Mat &old_noised) = 0;

    virtual float getInitNoiseSigma() = 0;

    virtual cv::Mat randn_mat(int seed, int height, int width, int is_latent_sample) = 0;

    virtual std::vector<float> get_timesteps() = 0;

    virtual std::vector<float> get_sigmas() = 0;

    virtual void set_init_sigma(float sigma) = 0;
};


#endif //STABLEDIFFUSION_SCHEDULER_BASE_H
