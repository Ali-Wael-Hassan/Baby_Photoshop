#include "menu.h"
#include <QDebug>
#include <algorithm>

Menu::Menu(QObject *parent) : QObject(parent) {
    QFile file("recentProjects.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString line = "";
    int i = 0;
    while(!in.atEnd()) {
        line = in.readLine();
        if(!QFile::exists(line)) {
            continue;
        }
        recent.push_back(line);
        ++i;
    }
    file.close();
}

void Menu::pushToUndo() {
    undo.push({img, currentImageName});
    while (!redo.empty()) redo.pop();
    emitStackSignals();
}

void Menu::emitStackSignals() {
    emit undoAvailable(!undo.empty());
    emit redoAvailable(!redo.empty());
}

bool Menu::loadImage(const QString &fileName, bool mine) {
    if (fileName.isEmpty()) {
        emit errorOccurred("File name is empty");
        return false;
    }
    std::string name = fileName.toStdString();

    if(name.substr(0,8) == "file:///") {
        name.erase(0,8);
    }

    QString fileName2 = QString::fromStdString(name);

    Image temp;
    try {
        temp.loadNewImage(fileName2.toStdString());
    } catch (const std::exception &e) {
        emit errorOccurred(QString::fromStdString(e.what()));
        return false;
    }

    pushToUndo();
    std::swap(img, temp);
    currentImageName = fileName2;

    if(mine) {
        emit imageChanged();
        emit saveSuccess("Loaded Successfully");
    }

    return true;
}

void Menu::saveImage(const QString &fileName, bool mine) {
    std::string name = fileName.toStdString();

    if(name.substr(0,8) == "file:///") {
        name.erase(0,8);
    }

    QString path = QString::fromStdString(name);

    try {
        img.saveImage(path.toStdString());
    } catch (const std::exception &e) {
        emit errorOccurred(QString::fromStdString(e.what()));
        return;
    }
    if(mine) emit saveSuccess("Saved successfully");
    if(!mine) return;
    QFile file("recentProjects.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    std::vector<QString> paths;
    std::set<QString> st;
    st.insert(fileName);
    paths.push_back(fileName);
    QString line = "";
    int size = 1;
    while(!in.atEnd()) {
        line = in.readLine();
        if(!QFile::exists(line)) {
            continue;
        }
        int oldSize = st.size();
        st.insert(line);
        if(oldSize != st.size()) paths.push_back(line), ++size;
    }
    file.close();
    QFile file2("recentProjects.txt");
    file2.open(QIODevice::WriteOnly);
    QTextStream out(&file2);
    for(auto& i : paths) {
        out << i << '\n';
    }
    file2.close();
    recent.clear();
    for(int i = 0; i < size; ++i) {
        recent.push_back(paths[i]);
    }
    emit refreshRecent();
}

void Menu::grayScale() {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    pushToUndo();
    applyFilter.grayScale(img);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

void Menu::blackWhite() {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    pushToUndo();
    applyFilter.blackWhite(img);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

void Menu::invertImage() {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    pushToUndo();
    applyFilter.invertImage(img);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

void Menu::mergeImage(const QString &fileName, int option, int transparency, int x1, int y1, int x2, int y2, int w, int h) {
    if (fileName.isEmpty()) {
        emit errorOccurred("Merge file name is empty");
        return;
    }
    if(w <= 0 || h <= 0) {
        emit errorOccurred("No overlap");
        return;
    }
    std::string name = fileName.toStdString();

    if(name.substr(0,8) == "file:///") {
        name.erase(0,8);
    }

    QString fileName2 = QString::fromStdString(name);

    Image mergeImg;
    try {
        mergeImg.loadNewImage(fileName2.toStdString());
    } catch (const std::exception &e) {
        emit errorOccurred(QString::fromStdString(e.what()));
        return;
    }

    pushToUndo();
    applyFilter.mergeImage(img, mergeImg, option, transparency, x1, y1, x2, y2, w, h);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

void Menu::flipImage(bool horizontal) {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    pushToUndo();
    applyFilter.flipImage(img, horizontal);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

void Menu::rotateImage(int degree) {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    if (degree % 90 != 0) {
        emit errorOccurred("Degree must be divisible by 90");
        return;
    }
    pushToUndo();
    applyFilter.rotateImage(img, degree);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

void Menu::brightness(int percent) {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    pushToUndo();
    applyFilter.darkenLightn(img, percent);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

void Menu::cropImage(int x, int y, int width, int height) {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    pushToUndo();
    applyFilter.cropImage(img, {x, y}, {width, height});
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

void Menu::detectEdges(int sharpness) {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    int threshold = 120 - 0.9 * sharpness;
    pushToUndo();
    applyFilter.detectEdges(img, threshold);
    emit imageChanged();
    emit saveSuccess("Done successfully");
}

void Menu::resizeImage(int width, int height) {
    pushToUndo();
    applyFilter.resizeImage(img, width, height);
    emit imageChanged();
    emit saveSuccess("Done successfully");
}

void Menu::blurImage(int type, int radiusOrPercent) {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    pushToUndo();

    applyFilter.boxBlur(img, radiusOrPercent);
    applyFilter.boxBlur(img, radiusOrPercent+1);
    applyFilter.boxBlur(img, radiusOrPercent+2);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

void Menu::contrast(int percent) {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    pushToUndo();
    applyFilter.contrast(img, percent);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

void Menu::purbleFilter() {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    pushToUndo();
    applyFilter.purbleFilter(img);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

void Menu::infraredFilter() {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    pushToUndo();
    applyFilter.infraredFilter(img);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

void Menu::sun(int percent) {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    pushToUndo();
    applyFilter.sun(img, percent);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

void Menu::tv() {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    pushToUndo();
    applyFilter.tv(img);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

void Menu::addFrame(const QString &fileName, int r, int g, int b) {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    if(fileName == "") {
        emit errorOccurred("No frame selected");
        return;
    }
    pushToUndo();
    Image temp(getAppDirPath().toStdString() + fileName.toStdString());
    applyFilter.addFrame(img, temp, r, g, b);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}


void Menu::skew(int degree) {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    pushToUndo();
    applyFilter.skew(img, acos(-1)/180 * degree);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

void Menu::oilPainting(int percent) {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    pushToUndo();
    percent = std::max(1, percent / 10);
    applyFilter.oilPainting(img, percent, 20);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

void Menu::undoF() {
    if (undo.empty()) {
        emit errorOccurred("Nothing to undo");
        return;
    }
    redo.push({img, currentImageName});
    img = undo.top().first;
    currentImageName = undo.top().second;
    undo.pop();
    emit imageChanged();
    emitStackSignals();
}

void Menu::redoF() {
    if (redo.empty()) {
        emit errorOccurred("Nothing to redo");
        return;
    }
    undo.push({img, currentImageName});
    img = redo.top().first;
    currentImageName = redo.top().second;
    redo.pop();
    emit imageChanged();
    emitStackSignals();
}

void Menu::oldPhoto() {
    if(currentImageName.isEmpty()) {
        emit errorOccurred("There is no image");
        return;
    }
    pushToUndo();
    applyFilter.oldPhoto(img);
    emit saveSuccess("Done successfully");
    emit imageChanged();
}

QString Menu::cleanName() const {
    QString name = "";
    for(int i = currentImageName.size() - 1; i >= 0; --i) {
        if(currentImageName[i] == '/') break;
        name.push_back(currentImageName[i]);
    }

    std::reverse(name.begin(), name.end());

    return name;
}
