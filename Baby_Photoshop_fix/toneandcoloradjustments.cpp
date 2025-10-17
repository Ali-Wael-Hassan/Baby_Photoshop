#include "toneandcoloradjustments.h"

// Ali Wael 20240354
void ToneAndColorAdjustments::grayScale(Image &orig) {
    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            int R = orig(x,y,0),
                G = orig(x,y,1),
                B = orig(x,y,2);

            int gray= std::min(0.299f*R+0.587f*G+0.114f*B + 0.5f, 255.0f);

            for(int c = 0; c < orig.channels; ++ c) {
                orig(x,y,c) = gray;

            }
        }
    }
}

// Amr Atif 20240398
void ToneAndColorAdjustments::blackWhite(Image &orig) {
    grayScale(orig);
    for(int i = 0;i<orig.width;i++){
        for(int j = 0;j<orig.height;j++){
            for(int c = 0;c<orig.channels;c++){
                orig(i,j,c)=((orig(i,j,c)>=128)? 255:0);
            }
        }
    }
}

// Youssef Mohamed Hassib 20240707
void ToneAndColorAdjustments::invertImage(Image &orig) {
    for (int i = 0; i < orig.width; ++i) {
        for (int j = 0; j < orig.height; ++j) {
            orig(i, j, 0) = 255 - orig(i, j, 0);
            orig(i, j, 1) = 255 - orig(i, j, 1);
            orig(i, j, 2) = 255 - orig(i, j, 2);
        }
    }
}


//Ali Wael 20240354
void ToneAndColorAdjustments::darkenLightn(Image &orig, int percent) {
    // percent -100 to 100
    float v = std::pow((float) std::abs(percent) / 100,1.5);

    bool dark = 0;
    if(percent < 0) dark = 1;

    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            for(int c = 0; c < orig.channels; ++c) {
                if(dark) orig(x,y,c) = std::max(0.0f,(1-v) * orig(x,y,c));
                else orig(x,y,c) = std::min(255.0f,(1+v) * orig(x,y,c));
            }
        }
    }
}

// Ali Wael 20240354
void ToneAndColorAdjustments::contrast(Image &orig, int percent){
    // -100 to 100
    float v = 1.0f + (float) percent / 100;
    if(percent >= 0) v = 1.0f + (float) percent / 100;
    else v = 1.0f + (float) percent / 200;

    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            for(int c = 0; c < orig.channels; ++c) {
                float val = (orig(x,y,c)-128.0f) * v + 128.0f;
                val = std::max(0.0f,std::min(255.0f,val));
                orig(x,y,c) = val;
            }
        }
    }
}
// Amr Atif 20240398
void ToneAndColorAdjustments::purbleFilter(Image &orig)
{
    for (int i = 0; i < orig.width; i++) {
        for (int j = 0; j < orig.height; j++) {

            float R_new = std::min(std::max(orig(i, j, 0) * 1.2 + 10.0, 0.0), 255.0);
            float G_new = std::min(std::max(orig(i, j, 1) * 0.8 - 10.0, 0.0), 255.0);
            float B_new = std::min(std::max(orig(i, j, 2) * 1.3 + 20.0, 0.0), 255.0);

            orig(i, j, 0) = static_cast<unsigned char>(R_new);
            orig(i, j, 1) = static_cast<unsigned char>(G_new);
            orig(i, j, 2) = static_cast<unsigned char>(B_new);
        }
    }
}
// Amr Atif 20240398
void ToneAndColorAdjustments::infraredFilter(Image &orig)
{
    grayScale(orig);
    invertImage(orig);

    for (int y = 0; y < orig.height; ++y)
        for (int x = 0; x < orig.width; ++x) {
            orig(x, y, 1) = orig(x,y,0);
            orig(x, y, 2) = orig(x,y,0);
            orig(x,y,0) = 255;
        }
}
// Youssef Mohamed Hassib 20240707
void ToneAndColorAdjustments::sun(Image &orig, int percent) {

    float intensity = (float) percent / 100;
    for (int y = 0; y < orig.height; ++y) {
        for (int x = 0; x < orig.width; ++x) {
            float avg = 0.0;
            for (int i = 0; i < 3; ++i) {
                avg += orig(x, y, i);
            }
            avg /= 3;

            float ry = std::min(avg * 1.95, 255.0);
            float gy = std::min(avg * 1.80, 255.0);
            float by = std::min(avg * 0.85, 255.0);

            float r = orig(x, y, 0) * (1 - intensity) + ry * intensity;
            float g = orig(x, y, 1) * (1 - intensity) + gy * intensity;
            float b = orig(x, y, 2) * (1 - intensity) + by * intensity;

            orig(x, y, 0) = std::min(255.0f, std::max(r, 0.0f));
            orig(x, y, 1) = std::min(255.0f, std::max(g, 0.0f));
            orig(x, y, 2) = std::min(255.0f, std::max(b, 0.0f));


        }
    }
}
// Youssef Mohamed Hassib 20240707
void ToneAndColorAdjustments::tv(Image &orig) {
    Image temp(orig);
    const float PI = acos(-1);
    for (int y = 0; y < orig.height; ++y) {
        float dark = ((y/3) % 2 == 1? 0.4f : 1.0f);
        for (int x = 0; x < orig.width; ++x) {
            float noise = 1.0f + (((std::rand())%11) - 5) / 100.0f;
            for(int c = 0; c < orig.channels; ++c) {
                temp(x,y,c) = std::min(255.0f,std::max(orig(x,y,c) * dark * noise,0.0f));
            }
        }
    }
    std::swap(orig,temp);
}

void ToneAndColorAdjustments::oldPhoto(Image &orig) {
    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            int r = orig(x,y,0), g = orig(x,y,1), b = orig(x,y,2);
            orig(x,y,0) = std::min(255.0f, std::max(0.0f, r * 0.393f + g * 0.769f + b * 0.189f));
            orig(x,y,1) = std::min(255.0f, std::max(0.0f, r * 0.349f + g * 0.686f + b * 0.168f));
            orig(x,y,2) = std::min(255.0f, std::max(0.0f, r * 0.272f + g * 0.534f + b * 0.131f));
        }
    }
}
