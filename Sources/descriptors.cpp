#include "follower.hpp"

#include <aubio.h>

std::vector<float> FollowerScore::getPitch(t_sample *in) {
    fvec_t *out = new_fvec(1);
    aubio_pitchyinfft_t *p = new_aubio_pitchyinfft(Sr, BlockSize);
    aubio_pitchyinfft_set_tolerance(p, 0.2);
    // aubio_pitchyinfft_do(p, in, out);
    // fvec_print(out);

    return std::vector<float>();
}
