#include "artisticeffects.h"

// Ali Wael 20240354
void ArtisticEffects::detectEdges(Image &orig, int threshold) {
    apply.grayScale(orig);
    blurImage(orig, 2.5);

    Image temp(orig);

    int w = orig.width;
    int h = orig.height;

    int g1[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int g2[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

    for (int x = 1; x < w - 1; ++x) {
        for (int y = 1; y < h - 1; ++y) {
            int sum1 = 0, sum2 = 0;

            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    float val = orig(x + dx, y + dy, 0);
                    sum1 += val * g1[dy + 1][dx + 1];
                    sum2 += val * g2[dy + 1][dx + 1];
                }
            }

            int out = (sum1 * sum1 + sum2 * sum2 >= threshold * threshold ? 0 : 255);
            for(int c = 0; c < orig.channels; ++c) {
                temp(x,y,c) = out;
            }
        }
    }

    std::swap(orig,temp);
}

// Youssef Mohamed Hassib 20240707
void ArtisticEffects::generateKernel(std::vector<float>& kernel, float sigma) { // generates the kernel used to blur efficiently
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
    std::vector<float> kernel;
    generateKernel(kernel, alpha);
    int half = kernel.size() / 2;
    Image temp(orig);
    // Blurring horizontally (1D)
    for (int y = 0; y < temp.height; ++y) {
        for (int x = 0; x < temp.width; ++x) {
            for (int c = 0; c < temp.channels; ++c) {
                float val = 0;
                for (int dk = -half; dk <= half; ++dk) {
                    int x2 = std::max(0, std::min(x + dk, temp.width - 1));
                    val += orig(x2, y, c) * kernel[dk + half];
                }
                temp(x, y, c) = std::min(255.0f, std::max(val, 0.0f));
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
                    int y2 = std::max(0, std::min(y + dk, temp.height - 1));
                    val += orig(x, y2, c) * kernel[dk + half];
                }

                temp(x, y, c) = std::min(255.0f, std::max(val, 0.0f));
            }
        }
    }
    std::swap(orig,temp);
}

void ArtisticEffects::boxBlur(Image &orig, int radius) {
    using vi = std::vector<int>;
    using vvi = std::vector<vi>;
    using vvvi = std::vector<vvi>;
    vvvi pre(orig.height + 1, vvi(orig.width + 1, vi(orig.channels, 0)));
    for (int i = 0; i <= orig.width; ++i) {
        for (int j = 0; j <= orig.height; ++j) {
            for (int k = 0; k < orig.channels; ++k) {
                if(i && j )pre[j][i][k] = orig(i-1, j-1, k);
                if (i)pre[j][i][k] += pre[j][i - 1][k];
                if(j)pre[j][i][k] += pre[j-1][i][k];
                if(i && j) pre[j][i][k] -= pre[j-1][i-1][k];
            }
        }
    }

    for (int i = 0; i < orig.width; ++i) {
        for (int j = 0; j < orig.height; ++j) {
            for (int k = 0; k < orig.channels; ++k) {
                int x1 = std::max(0, i - radius);
                int x2 = std::min(i + radius, orig.width - 1);
                int y1 = std::max(0, j - radius);
                int y2 = std::min(j + radius, orig.height - 1);

                int count = (y2 - y1 + 1) * (x2 - x1 + 1);
                int sum = pre[y2+1][x2+1][k] + pre[y1][x1][k] - pre[y2+1][x1][k] - pre[y1][x2+1][k];
                orig(i,j,k) = sum/count;
            }
        }
    }
}

// Ali Wael 20240354
void ArtisticEffects::oilPainting(Image &orig, int radius, int intensityLevel)
{
    using vi = std::vector<int>;
    using vvi = std::vector<vi>;

    intensityLevel = std::min(intensityLevel, 20);

    Image temp(orig);

    vvi intensityMap(orig.width, vi(orig.height));
    for (int x = 0; x < orig.width; ++x) {
        for (int y = 0; y < orig.height; ++y) {
            int r = orig(x,y,0), g = orig(x,y,1), b = orig(x,y,2);
            intensityMap[x][y] = ((r + g + b) * intensityLevel) / (3 * 255);
        }
    }

    std::vector<int> bin(intensityLevel + 1, 0), red(intensityLevel + 1, 0) , green(intensityLevel + 1, 0), blue(intensityLevel + 1, 0);

    for (int y = 0; y < orig.height; ++y) {
        fill(bin.begin(), bin.end(), 0);
        fill(red.begin(), red.end(), 0);
        fill(green.begin(), green.end(), 0);
        fill(blue.begin(), blue.end(), 0);
        for(int dx = 0; dx <= radius; ++dx) {
            if(dx >= orig.width) continue;
            for(int dy = -radius; dy <= radius; ++dy) {
                int ny = y + dy;
                if(ny < 0 || ny >= orig.height) continue;

                int i = intensityMap[dx][ny];
                bin[i]++;
                red[i] += orig(dx,ny,0);
                green[i] += orig(dx,ny,1);
                blue[i] += orig(dx,ny,2);
            }
        }

        for (int x = 0; x < orig.width; ++x) {
            int bestI = 0, bestCount = 0;
            for (int i = 0; i <= intensityLevel; ++i) {
                if (bin[i] > bestCount) {
                    bestCount = bin[i], bestI = i;
                }
            }
            temp(x,y,0) = red[bestI] / bestCount;
            temp(x,y,1) = green[bestI] / bestCount;
            temp(x,y,2) = blue[bestI] / bestCount;

            int x1 = x - radius;

            if(x1 >= 0) {
                for(int dy = -radius; dy <= radius; ++dy) {
                    int ny = y + dy;
                    if(ny < 0 || ny >= orig.height) continue;

                    int i = intensityMap[x1][ny];
                    bin[i]--;
                    red[i] -= orig(x1,ny,0);
                    green[i] -= orig(x1,ny,1);
                    blue[i] -= orig(x1,ny,2);
                }
            }

            int x2 = x + radius + 1;

            if(x2 < orig.width) {
                for(int dy = -radius; dy <= radius; ++dy) {
                    int ny = y + dy;
                    if(ny < 0 || ny >= orig.height) continue;

                    int i = intensityMap[x2][ny];
                    bin[i]++;
                    red[i] += orig(x2,ny,0);
                    green[i] += orig(x2,ny,1);
                    blue[i] += orig(x2,ny,2);
                }
            }
        }
    }

    std::swap(orig, temp);
}
