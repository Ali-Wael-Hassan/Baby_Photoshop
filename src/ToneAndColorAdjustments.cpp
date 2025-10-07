#include "Winged_Dragon/ToneAndColorAdjustments.h"

// Ali Wael 20240354
void ToneAndColorAdjustments::grayScale(Image &orig) {
    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            int R = orig(x,y,0),
                G = orig(x,y,1),
                B = orig(x,y,2);
            
            int gray= min(0.299f*R+0.587f*G+0.114f*B + 0.5f, 255.0f);

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


//Ali-Wael 20240354
void ToneAndColorAdjustments::darkenLightn(Image &orig, int percent) {
    // percent -100 to 100
    float v = pow((float) std::abs(percent) / 100,1.5);
    
    bool dark = 0;
    if(percent < 0) dark = 1;
    
    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            for(int c = 0; c < orig.channels; ++c) {
                if(dark) orig(x,y,c) = max(0.0f,(1-v) * orig(x,y,c));
                else orig(x,y,c) = min(255.0f,(1+v) * orig(x,y,c));
            }
        }
    }
}

// Ali-Wael 20240354
void ToneAndColorAdjustments::contrast(Image &orig, int percent){ 
    // -100 to 100
    float v = 1.0f + (float) percent / 100;
    if(percent >= 0) v = 1.0f + (float) percent / 100;
    else v = 1.0f + (float) percent / 200;
    
    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            for(int c = 0; c < orig.channels; ++c) {
                float val = (orig(x,y,c)-128.0f) * v + 128.0f;
                val = max(0.0f,min(255.0f,val));
                orig(x,y,c) = val;
            }
        }
    }
}

void ToneAndColorAdjustments::purbleFilter(Image &orig)
{
    for (int i = 0; i < orig.width; i++) {
        for (int j = 0; j < orig.height; j++) {

            float R_new =min(max(orig(i, j, 0) * 1.2 + 10.0, 0.0), 255.0);
            float G_new =min(max(orig(i, j, 1) * 0.8 - 10.0, 0.0), 255.0);
            float B_new =min(max(orig(i, j, 2) * 1.3 + 20.0, 0.0), 255.0);

            orig(i, j, 0) = static_cast<unsigned char>(R_new);
            orig(i, j, 1) = static_cast<unsigned char>(G_new);
            orig(i, j, 2) = static_cast<unsigned char>(B_new);
        }
    }
}

void ToneAndColorAdjustments::infraredFilter(Image &orig,float precent)
{
    invertImage(orig);
    for (int i = 0; i < orig.width; ++i) {
        for (int j = 0; j < orig.height; ++j) {
            orig(i, j, 0) = min(255.0f,max(0.0f,(orig(i, j, 0) + 100) * (1 + precent)));
        }
    }
}


void ToneAndColorAdjustments::sun(Image &orig, int percent) {

    double intensity = (double) percent / 100;
    for (int y = 0; y < orig.height; ++y) {
        for (int x = 0; x < orig.width; ++x) {
            double avg = 0.0;
            for (int i = 0; i < 3; ++i) {
                avg += orig(x, y, i);
            }
            avg /= 3;

            double ry = min(avg * 1.95, 255.0);
            double gy = min(avg * 1.80, 255.0);
            double by = min(avg * 0.85, 255.0);

            double r = orig(x, y, 0) * (1 - intensity) + ry * intensity;
            double g = orig(x, y, 1) * (1 - intensity) + gy * intensity;
            double b = orig(x, y, 2) * (1 - intensity) + by * intensity;

            orig(x, y, 0) = min(255.0, max(r, 0.0));
            orig(x, y, 1) = min(255.0, max(g, 0.0));
            orig(x, y, 2) = min(255.0, max(b, 0.0));


        }
    }
}

void ToneAndColorAdjustments::tv(Image &orig) {
    for (int y = 0; y < orig.height; ++y) {
        for (int x = 0; x < orig.width; ++x) {
            if (y % 2) {
                for (int k = 0; k < 3; ++k) {
                    double val = orig(x, y, k) - orig(x, y, k) * 0.4;
                    orig(x, y, k) = min(255.0, max(0.0, val));

                }
            }
        }
    }
}