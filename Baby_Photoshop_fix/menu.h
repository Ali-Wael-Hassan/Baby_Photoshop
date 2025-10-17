#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <stack>
#include <string>
#include <QCoreApplication>
#include "manager.h"
#include <QTextStream>
#include <QFile>
#include <set>

class Menu : public QObject
{
    Q_OBJECT
public:
    explicit Menu(QObject *parent = nullptr);

    Q_INVOKABLE bool loadImage(const QString &fileName, bool mine = true);
    Q_INVOKABLE void saveImage(const QString &fileName = QString(), bool mine = true);
    Q_INVOKABLE void grayScale();
    Q_INVOKABLE void blackWhite();
    Q_INVOKABLE void invertImage();
    Q_INVOKABLE void mergeImage(const QString &fileName, int option = 1, int transparency = 50, int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, int w = 0, int h = 0);
    Q_INVOKABLE void flipImage(bool horizontal = true);
    Q_INVOKABLE void rotateImage(int degree);
    Q_INVOKABLE void brightness(int percent);
    Q_INVOKABLE void cropImage(int x, int y, int width, int height);
    Q_INVOKABLE void detectEdges(int sharpness);
    Q_INVOKABLE void resizeImage(int width, int height);
    Q_INVOKABLE void blurImage(int type = 1, int radiusOrPercent = 10);
    Q_INVOKABLE void contrast(int percent);
    Q_INVOKABLE void purbleFilter();
    Q_INVOKABLE void infraredFilter();
    Q_INVOKABLE void sun(int percent);
    Q_INVOKABLE void tv();
    Q_INVOKABLE void addFrame(const QString &fileName, int r, int b, int g);
    Q_INVOKABLE void skew(int degree);
    Q_INVOKABLE void oilPainting(int percent);
    Q_INVOKABLE void undoF();
    Q_INVOKABLE void redoF();
    Q_INVOKABLE QString getName() const {return currentImageName;}
    Q_INVOKABLE QString cleanName() const;
    Q_INVOKABLE QString getAppDirPath() const {return QCoreApplication::applicationDirPath();}
    Q_INVOKABLE QString getRecent(int i) const {return (i < recent.size()? recent[i] : "");}
    Q_INVOKABLE bool isImageEmpty() {return img.imageData == nullptr;}
    Q_INVOKABLE void oldPhoto();

signals:
    void imageChanged();
    void undoAvailable(bool available);
    void redoAvailable(bool available);
    void errorOccurred(const QString &msg);
    void saveSuccess(const QString &msg);
    void refreshRecent();

private:
    Manager applyFilter;
    Image img;
    std::stack<std::pair<Image, QString>> undo, redo;
    QString currentImageName = "";
    std::vector<QString> recent;

    void pushToUndo();
    void emitStackSignals();
};

#endif // MENU_H
