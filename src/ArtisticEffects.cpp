#include "Winged_Dragon/ArtisticEffects.h"

#define vf vector<float>
#define vvf vector<vector<float>>

// Ali Wael 20240354
void ArtisticEffects::detectEdges(Image &orig, float alpha, int tresh) {
    apply.grayScale(orig);
    blurImage(orig, alpha);

    int w = orig.width;
    int h = orig.height;

    int g1[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int g2[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

    float *arr = new float[w*h], mx = 0.0f;

    for (int x = 1; x < w - 1; ++x) {
        for (int y = 1; y < h - 1; ++y) {
            float sum1 = 0, sum2 = 0;
            
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    float val = orig(x + dx, y + dy, 0);
                    sum1 += val * g1[dy + 1][dx + 1];
                    sum2 += val * g2[dy + 1][dx + 1];
                }
            }
            
            float grad = sqrt(sum1 * sum1 + sum2 * sum2);

            arr[y * w + x] = grad;
        }
    }

    for (int x = 1; x < w - 1; ++x) {
        for (int y = 1; y < h - 1; ++y) {
            int out = (arr[y * w + x] >= tresh? 0 : 255);
            for(int c = 0; c < orig.channels; ++c) {
                orig(x,y,c) = out;
            }
        }
    }

    delete [] arr;
}

// Youssef Mohamed Hassib 20240707
void ArtisticEffects::generateKernel(vf& kernel, float sigma) { // generates the kernel used to blur efficiently
    int radius = ceil(3 * sigma);
    int size = 2 * radius + 1;
    kernel.assign(size, 0.0f);

    float sum = 0;
    float PI = acos(-1.0f);

    for (int x = -radius; x <= radius; ++x) {
        float G = exp(-(x * x) / (2 * sigma * sigma)) / (2 * PI * sigma * sigma);
        kernel[x + radius] = G;
        sum += G;
    }

    for (int x = 0; x < size; ++x)
        kernel[x] /= sum;
}

// Youssef Mohamed Hassib 20240707
void ArtisticEffects::blurImage(Image &orig, float alpha) {
    if(alpha < 1e-9) return;
    vf kernel;
    generateKernel(kernel, alpha);
    int half = kernel.size() / 2;
    Image temp(orig);
    // Blurring horizontally (1D)
    for (int y = 0; y < temp.height; ++y) {
        for (int x = 0; x < temp.width; ++x) {
            for (int c = 0; c < temp.channels; ++c) {
                float val = 0;
                for (int dk = -half; dk <= half; ++dk) {
                    int x2 = max(0, min(x + dk, temp.width - 1));
                    val += orig(x2, y, c) * kernel[dk + half];
                }
                temp(x, y, c) = min(255.0f, max(val, 0.0f));
            }
        }
    }

    orig = temp;
    // Blurring vertically (1D)
    for (int y = 0; y < temp.height; ++y) {
        for (int x = 0; x < temp.width; ++x) {
            for (int c = 0; c < temp.channels; ++c) {
                float val = 0;
                for (int dk = -half; dk <= half; ++dk) {
                    int y2 = max(0, min(y + dk, temp.height - 1));
                    val += orig(x, y2, c) * kernel[dk + half];
                }

                temp(x, y, c) = min(255.0f, max(val, 0.0f));
            }
        }
    }
    swap(orig,temp);
}

// Ali Wael 20240354
void ArtisticEffects::oilPainting(Image &orig, int radius, int intensityLevel)
{
    using vi = vector<int>;
    using vvi = vector<vi>;

    radius = 2 * radius + 1;
    intensityLevel = min(intensityLevel, 20);

    Image temp(orig);

    vvi intensityMap(orig.width, vi(orig.height));
    for (int x = 0; x < orig.width; ++x) {
        for (int y = 0; y < orig.height; ++y) {
            int r = orig(x,y,0), g = orig(x,y,1), b = orig(x,y,2);
            intensityMap[x][y] = ((r + g + b) * intensityLevel) / (3 * 255);
        }
    }

    for (int x = 0; x < orig.width; ++x) {

        int *bin = new int[intensityLevel + 2]{};
        int *red = new int[intensityLevel + 2]{};
        int *green = new int[intensityLevel + 2]{};
        int *blue = new int[intensityLevel + 2]{};

        for (int y = 0; y < orig.height; ++y) {
            fill(bin, bin + intensityLevel + 2, 0);
            fill(red, red + intensityLevel + 2, 0);
            fill(green, green + intensityLevel + 2, 0);
            fill(blue, blue + intensityLevel + 2, 0);
            int bestI = 0, bestCount = 0;
            for (int dx = -radius; dx <= radius; ++dx)
                for (int dy = -radius; dy <= radius; ++dy) {
                    int nx = x + dx, ny = y + dy;
                    if (nx < 0 || nx >= orig.width || ny < 0 || ny >= orig.height) continue;

                    int i = intensityMap[nx][ny];
                    bin[i]++;
                    red[i] += orig(nx,ny,0);
                    green[i] += orig(nx,ny,1);
                    blue[i] += orig(nx,ny,2);

                    if (bin[i] > bestCount) {
                        bestCount = bin[i];
                        bestI = i;
                    }
                }

            temp(x,y,0) = red[bestI] / bestCount;
            temp(x,y,1) = green[bestI] / bestCount;
            temp(x,y,2) = blue[bestI] / bestCount;
        }
        delete [] bin;
        delete [] red;
        delete [] green;
        delete [] blue;
    }

    swap(orig, temp);
}