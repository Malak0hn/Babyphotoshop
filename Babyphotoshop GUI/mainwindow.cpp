#include "mainwindow.h"
#include "./ui_mainwindow.h"

void grayscale(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int avg = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
}

void blackandwhite(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int avr = 0;
            for (int k = 0; k < 3; k++) {
                avr += image(i, j, k);
            }
            avr /= 3;
            int val = (avr < 128) ? 0 : 255;
            for (int k = 0; k < 3; k++) {
                image(i, j, k) = val;
            }
        }
    }
}

void invert(Image& image) {
    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            image(x, y, 0) = 255 - image(x, y, 0);
            image(x, y, 1) = 255 - image(x, y, 1);
            image(x, y, 2) = 255 - image(x, y, 2);
        }
    }
}

void brighten(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int red = std::min(255, image(i, j, 0) + 35);
            int green = std::min(255, image(i, j, 1) + 25);
            int blue = std::min(255, image(i, j, 2) + 15);
            image(i, j, 0) = red;
            image(i, j, 1) = green;
            image(i, j, 2) = blue;
        }
    }
}

void purple(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int red = image(i, j, 0) + 50;
            int green = image(i, j, 1) / 2;
            int blue = image(i, j, 2) + 50;

            if (red > 255) red = 255;
            if (blue > 255) blue = 255;

            image(i, j, 0) = red;
            image(i, j, 1) = green;
            image(i, j, 2) = blue;
        }
    }
}

void irPhoto(Image& img) {
    for (int x = 0; x < img.width; ++x) {
        for (int y = 0; y < img.height; ++y) {
            int old_G = img(x, y, 1);
            int old_B = img(x, y, 2);
            img(x, y, 0) = 255;
            img(x, y, 1) = 255 - old_G;
            img(x, y, 2) = 255 - old_B;
        }
    }
}

void oilimage(Image& image) {
    Image finalImg = image;
    int levels = 20;
    int radius = 3;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int freq[20] = {0};
            int redsum[20] = {0};
            int greensum[20] = {0};
            int bluesum[20] = {0};
            for (int x = i - radius; x <= i + radius; x++) {
                for (int y = j - radius; y <= j + radius; y++) {
                    if (x >= 0 && x < image.width && y >= 0 && y < image.height) {
                        int red = finalImg(x, y, 0);
                        int green = finalImg(x, y, 1);
                        int blue = finalImg(x, y, 2);
                        int intensity = (red + green + blue) / 3;
                        int level = (intensity * levels) / 256;
                        if (level >= levels) level = levels - 1;
                        freq[level]++;
                        redsum[level] += red;
                        greensum[level] += green;
                        bluesum[level] += blue;
                    }
                }
            }
            int bestlevel = 0;
            for (int k = 1; k < levels; k++) {
                if (freq[k] > freq[bestlevel]) bestlevel = k;
            }
            if (freq[bestlevel] > 0) {
                image(i, j, 0) = redsum[bestlevel] / freq[bestlevel];
                image(i, j, 1) = greensum[bestlevel] / freq[bestlevel];
                image(i, j, 2) = bluesum[bestlevel] / freq[bestlevel];
            }
        }
    }
}

void flip(Image& image, const std::string& flipPosition) {
    if (flipPosition == "Horizontal" || flipPosition == "horizontal") {
        for (int i = 0; i < image.width / 2; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    int temp = image(i, j, k);
                    image(i, j, k) = image(image.width - 1 - i, j, k);
                    image(image.width - 1 - i, j, k) = temp;
                }
            }
        }
    } else if (flipPosition == "Vertical" || flipPosition == "vertical") {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height / 2; j++) {
                for (int k = 0; k < 3; k++) {
                    int temp = image(i, j, k);
                    image(i, j, k) = image(i, image.height - 1 - j, k);
                    image(i, image.height - 1 - j, k) = temp;
                }
            }
        }
    }
}

void rotateimage(Image& image, int rotation_angle) {
    int w = image.width, h = image.height;
    if (rotation_angle == 90) {
        Image rotated(h, w);
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                for (int k = 0; k < 3; k++) {
                    rotated(h - 1 - j, i, k) = image(i, j, k);
                }
            }
        }
        image = rotated;
    } else if (rotation_angle == 180) {
        Image rotated(w, h);
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                for (int k = 0; k < 3; k++) {
                    rotated(w - 1 - i, h - 1 - j, k) = image(i, j, k);
                }
            }
        }
        image = rotated;
    } else if (rotation_angle == 270) {
        Image rotated(h, w);
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                for (int k = 0; k < 3; k++) {
                    rotated(j, w - 1 - i, k) = image(i, j, k);
                }
            }
        }
        image = rotated;
    }
}

void framer(Image &img, int opt) {
    int t = std::min(img.width, img.height) / 10;
    int t1 = std::min(img.width, img.height) / 15;
    int t2 = std::min(img.width, img.height) / 30;

    for (int x = 0; x < img.width; ++x) {
        for (int y = 0; y < img.height; ++y) {
            if (x < t || x >= img.width - t || y < t || y >= img.height - t) {
                img(x, y, 0) = 10;
                img(x, y, 1) = 35;
                img(x, y, 2) = 90;
            }
        }
    }

    if (opt == 2) {
        for (int x = 0; x < img.width; ++x) {
            for (int y = 0; y < img.height; ++y) {
                if (x < t1 || x >= img.width - t1 || y < t1 || y >= img.height - t1) {
                    img(x, y, 0) = 25;
                    img(x, y, 1) = 80;
                    img(x, y, 2) = 200;
                }
            }
        }

        for (int x = 0; x < img.width; ++x) {
            for (int y = 0; y < img.height; ++y) {
                if (x < t2 || x >= img.width - t2 || y < t2 || y >= img.height - t2) {
                    img(x, y, 0) = 50;
                    img(x, y, 1) = 50;
                    img(x, y, 2) = 50;
                }
            }
        }
    }
}

void darkenlighten(Image& image, int choice, int value) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                int newValue = image(i, j, k);

                if (choice == 1)
                    newValue -= value;
                else if (choice == 2)
                    newValue += value;

                if (newValue > 255) newValue = 255;
                if (newValue < 0) newValue = 0;

                image(i, j, k) = newValue;
            }
        }
    }
}

void resizeImage(Image &img, int new_w, int new_h) {
    if (new_w <= 0 || new_h <= 0) return;
    int old_w = img.width;
    int old_h = img.height;

    Image resized_img(new_w, new_h);

    for (int y = 0; y < new_h; ++y) {
        int old_y = (y * old_h) / new_h;
        if (old_y >= old_h) old_y = old_h - 1;

        for (int x = 0; x < new_w; ++x) {
            int old_x = (x * old_w) / new_w;
            if (old_x >= old_w) old_x = old_w - 1;

            resized_img(x, y, 0) = img(old_x, old_y, 0);
            resized_img(x, y, 1) = img(old_x, old_y, 1);
            resized_img(x, y, 2) = img(old_x, old_y, 2);
        }
    }
    img = resized_img;
}

void bluring(Image &img, int lvl) {
    int sum_R, sum_G, sum_B;
    int r;
    int count_x;
    int ave_R, ave_G, ave_B;
    Image temp_img = img;

    switch (lvl) {
    case 1: r = 12; break;
    case 2: r = 14; break;
    case 3: r = 16; break;
    default: return;
    }

    for (int y = 0; y < img.height; ++y) {
        sum_R = 0; sum_G = 0; sum_B = 0; count_x = 0;
        for (int dx = 0; dx < r && dx < img.width; dx++) {
            sum_R += img(dx, y, 0);
            sum_G += img(dx, y, 1);
            sum_B += img(dx, y, 2);
            count_x++;
        }
        for (int x = 0; x < img.width; ++x) {
            if (x - r - 1 >= 0) {
                sum_R -= img(x - r - 1, y, 0);
                sum_G -= img(x - r - 1, y, 1);
                sum_B -= img(x - r - 1, y, 2);
                count_x--;
            }
            if (temp_img.width > x + r) {
                sum_R += img(x + r, y, 0);
                sum_G += img(x + r, y, 1);
                sum_B += img(x + r, y, 2);
                count_x++;
            }
            ave_R = sum_R / count_x;
            ave_G = sum_G / count_x;
            ave_B = sum_B / count_x;

            temp_img(x, y, 0) = ave_R;
            temp_img(x, y, 1) = ave_G;
            temp_img(x, y, 2) = ave_B;
        }
    }

    for (int x = 0; x < img.width; ++x) {
        sum_R = 0; sum_G = 0; sum_B = 0; int count = 0;
        for (int dy = 0; dy < r && dy < temp_img.height; dy++) {
            sum_R += temp_img(x, dy, 0);
            sum_G += temp_img(x, dy, 1);
            sum_B += temp_img(x, dy, 2);
            count++;
        }
        for (int y = 0; y < img.height; ++y) {
            if (y - r - 1 >= 0) {
                sum_R -= temp_img(x, y - r - 1, 0);
                sum_G -= temp_img(x, y - r - 1, 1);
                sum_B -= temp_img(x, y - r - 1, 2);
                count--;
            }
            if (img.height > y + r) {
                sum_R += temp_img(x, y + r, 0);
                sum_G += temp_img(x, y + r, 1);
                sum_B += temp_img(x, y + r, 2);
                count++;
            }

            ave_R = sum_R / count;
            ave_G = sum_G / count;
            ave_B = sum_B / count;
            img(x, y, 0) = ave_R;
            img(x, y, 1) = ave_G;
            img(x, y, 2) = ave_B;
        }
    }
}

void cropImage(Image& image, int x, int y, int W, int H) {
    if (W <= 0 || H <= 0) return;
    if (x < 0 || y < 0 || x + W > image.width || y + H > image.height) return;

    Image newImage(W, H);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            for (int k = 0; k < 3; k++) {
                newImage(j, i, k) = image(x + j, y + i, k);
            }
        }
    }
    image = newImage;
}

void skewFilter(Image& image, double angle) {
    double radians = angle * 3.14159265358979323846 / 180.0;
    double skew = tan(radians);

    int newHeight = image.height;
    double totalShift = (newHeight - 1) * skew;

    int extraWidth = static_cast<int>(ceil(abs(totalShift)));
    int newWidth = extraWidth + image.width;

    int offset = static_cast<int>(ceil(std::max(0.0, -totalShift)));

    Image output(newWidth, newHeight);

    for (int y = 0; y < newHeight; y++) {
        for (int x = 0; x < newWidth; x++) {
            for (int c = 0; c < 3; c++) {
                output(x, y, c) = 255;
            }
        }
    }

    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            int shift = static_cast<int>(round((image.height - 1 - y) * skew));
            int newX = x + shift + offset;
            if (newX >= 0 && newX < newWidth) {
                for (int c = 0; c < 3; c++) {
                    output(newX, y, c) = image(x, y, c);
                }
            }
        }
    }
    image = output;
}

void DetectImageEdges(Image& image) {
    Image finalImg(image.width, image.height);
    for (int i = 0; i < image.width - 1; i++) {
        for (int j = 0; j < image.height - 1; j++) {
            for (int k = 0; k < 3; k++) {
                finalImg(i, j, k) = 255;
            }
        }
    }
    int x = 25;
    for (int i = 0; i < image.width - 1; i++) {
        for (int j = 0; j < image.height - 1; j++) {
            int right = std::abs(image(i, j, 0) - image(i + 1, j, 0));
            int down = std::abs(image(i, j, 1) - image(i, j + 1, 1));
            int result = (right > x || down > x) ? 0 : 255;
            for (int k = 0; k < 3; k++) {
                finalImg(i, j, k) = result;
            }
        }
    }
    image = finalImg;
}

void oldphoto(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 1; j < image.height; j += 9) {
            unsigned int avr = 0;
            for (int k = 0; k < 3; k++) {
                image(i, j, k) = image(0.5 * i, j, k);
                avr += image(i, j, k);
            }
            avr /= 3;
            for (int k = 0; k < 3; k++) {
                image(i, j, k) = avr;
            }
        }
    }
}

void mergeImages(Image& image1, const Image& image2, int mode) {
    if (mode == 1) {
        Image resizedImg2(image1.width, image1.height);
        for (int y = 0; y < image1.height; ++y) {
            int old_y = (y * image2.height) / image1.height;
            if (old_y >= image2.height) old_y = image2.height - 1;
            for (int x = 0; x < image1.width; ++x) {
                int old_x = (x * image2.width) / image1.width;
                if (old_x >= image2.width) old_x = image2.width - 1;
                for (int k = 0; k < 3; ++k) {
                    resizedImg2(x, y, k) = image2(old_x, old_y, k);
                }
            }
        }

        for (int y = 0; y < image1.height; ++y) {
            for (int x = 0; x < image1.width; ++x) {
                for (int k = 0; k < 3; ++k) {
                    image1(x, y, k) = (image1(x, y, k) + resizedImg2(x, y, k)) / 2;
                }
            }
        }
    }
    else if (mode == 2) {
        int common_w = std::min(image1.width, image2.width);
        int common_h = std::min(image1.height, image2.height);

        Image mergedImg(common_w, common_h);
        for (int y = 0; y < common_h; ++y) {
            for (int x = 0; x < common_w; ++x) {
                for (int k = 0; k < 3; ++k) {
                    mergedImg(x, y, k) = (image1(x, y, k) + image2(x, y, k)) / 2;
                }
            }
        }
        image1 = mergedImg;
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.jpg *.jpeg *.png *.bmp)");

    if (fileName.isEmpty()) return;

    if (currentImage.loadNewImage(fileName.toStdString())) {
        isImageLoaded = true;
        displayImage();
    } else {
        QMessageBox::warning(this, "Error", "Failed to load image file!");
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if (!isImageLoaded) {
        QMessageBox::information(this, "Notice", "Please load an image first.");
        return;
    }

    int selectedIndex = ui->comboBox->currentIndex();

    switch (selectedIndex) {
    case 0:
        grayscale(currentImage);
        break;
    case 1:
        blackandwhite(currentImage);
        break;
    case 2:
        invert(currentImage);
        break;
    case 3: {
        QStringList frameTypes;
        frameTypes << "1. Normal Frame" << "2. Fancy Frame";
        bool ok;
        QString choice = QInputDialog::getItem(this, "Frame Filter", "Select Frame Style:", frameTypes, 0, false, &ok);
        if (ok && !choice.isEmpty()) {
            int opt = choice.startsWith("1") ? 1 : 2;
            framer(currentImage, opt);
        } else {
            return;
        }
        break;
    }
    case 4: {
        QStringList options;
        options << "Horizontal" << "Vertical";
        bool ok;
        QString choice = QInputDialog::getItem(this, "Flip Image", "Select Flip Direction:", options, 0, false, &ok);
        if (ok && !choice.isEmpty()) {
            flip(currentImage, choice.toStdString());
        } else {
            return;
        }
        break;
    }
    case 5: {
        QStringList angles;
        angles << "90" << "180" << "270";
        bool ok;
        QString choice = QInputDialog::getItem(this, "Rotate Image", "Select Angle:", angles, 0, false, &ok);
        if (ok && !choice.isEmpty()) {
            rotateimage(currentImage, choice.toInt());
        } else {
            return;
        }
        break;
    }
    case 6: {
        QStringList modes;
        modes << "1. Darken" << "2. Lighten";
        bool okMode;
        QString modeChoice = QInputDialog::getItem(this, "Darken / Lighten", "Choose Mode:", modes, 0, false, &okMode);
        if (!okMode || modeChoice.isEmpty()) return;

        bool okVal;
        int val = QInputDialog::getInt(this, "Adjustment Value", "Enter brightness value (1-255):", 50, 1, 255, 1, &okVal);
        if (okVal) {
            int choice = modeChoice.startsWith("1") ? 1 : 2;
            darkenlighten(currentImage, choice, val);
        } else {
            return;
        }
        break;
    }
    case 7: {
        bool okW, okH;
        int newW = QInputDialog::getInt(this, "Resize Image", "Enter new width:", currentImage.width, 1, 10000, 1, &okW);
        if (!okW) return;
        int newH = QInputDialog::getInt(this, "Resize Image", "Enter new height:", currentImage.height, 1, 10000, 1, &okH);
        if (!okH) return;

        resizeImage(currentImage, newW, newH);
        break;
    }
    case 8: {
        QString file2Name = QFileDialog::getOpenFileName(this, "Select Second Image to Merge", "", "Images (*.jpg *.jpeg *.png *.bmp)");
        if (file2Name.isEmpty()) return;

        Image image2;
        if (!image2.loadNewImage(file2Name.toStdString())) {
            QMessageBox::warning(this, "Error", "Failed to load second image!");
            return;
        }

        QStringList options;
        options << "1. Resize"
                << "2. Common Area";
        bool ok;
        QString choice = QInputDialog::getItem(this, "Merge Options", "Select Merge Method:", options, 0, false, &ok);
        if (!ok || choice.isEmpty()) return;

        int mode = choice.startsWith("1") ? 1 : 2;
        mergeImages(currentImage, image2, mode);
        break;
    }
    case 9: {
        DetectImageEdges(currentImage);
        break;
    }
    case 10: {
        bool okX, okY, okW, okH;
        int x = QInputDialog::getInt(this, "Crop Image", "Enter X start position:", 0, 0, currentImage.width - 1, 1, &okX);
        if (!okX) return;

        int y = QInputDialog::getInt(this, "Crop Image", "Enter Y start position:", 0, 0, currentImage.height - 1, 1, &okY);
        if (!okY) return;

        int w = QInputDialog::getInt(this, "Crop Image", "Enter crop width (px):", currentImage.width - x, 1, currentImage.width - x, 1, &okW);
        if (!okW) return;

        int h = QInputDialog::getInt(this, "Crop Image", "Enter crop height (px):", currentImage.height - y, 1, currentImage.height - y, 1, &okH);
        if (!okH) return;

        cropImage(currentImage, x, y, w, h);
        break;
    }
    case 11: {
        QStringList levels;
        levels << "1. Light Blur" << "2. Medium Blur" << "3. High Blur";
        bool ok;
        QString choice = QInputDialog::getItem(this, "Blur Filter", "Choose Blur Level:", levels, 0, false, &ok);
        if (ok && !choice.isEmpty()) {
            int lvl = choice.startsWith("1") ? 1 : (choice.startsWith("2") ? 2 : 3);
            bluring(currentImage, lvl);
        } else {
            return;
        }
        break;
    }
    case 12:
        brighten(currentImage);
        break;
    case 13: {
        oldphoto(currentImage);
        break;
    }
    case 14:
        purple(currentImage);
        break;
    case 15:
        irPhoto(currentImage);
        break;
    case 16: {
        bool ok;
        double angle = QInputDialog::getDouble(this, "Skew Image", "Enter skew angle (degrees):", 15.0, -80.0, 80.0, 1, &ok);
        if (ok) {
            skewFilter(currentImage, angle);
        } else {
            return;
        }
        break;
    }
    case 17:
        oilimage(currentImage);
        break;
    default:
        QMessageBox::information(this, "Info", "This interactive filter will be mapped next!");
        return;
    }

    displayImage();
}


void MainWindow::on_pushButton_3_clicked()
{
    if (!isImageLoaded) {
        QMessageBox::information(this, "Notice", "Please load an image first.");
        return;
    }

    QString savePath = QFileDialog::getSaveFileName(this, "Save Image", "output.jpg", "Images (*.jpg *.png *.bmp)");

    if (!savePath.isEmpty()) {
        currentImage.saveImage(savePath.toStdString());
        QMessageBox::information(this, "Success", "Image saved successfully!");
    }
}

void MainWindow::displayImage()
{
    if (!isImageLoaded) return;

    QImage qimg(currentImage.width, currentImage.height, QImage::Format_RGB888);

    for (int y = 0; y < currentImage.height; ++y) {
        uchar* line = qimg.scanLine(y);
        for (int x = 0; x < currentImage.width; ++x) {
            line[x * 3 + 0] = currentImage(x, y, 0);
            line[x * 3 + 1] = currentImage(x, y, 1);
            line[x * 3 + 2] = currentImage(x, y, 2);
        }
    }

    QPixmap pixmap = QPixmap::fromImage(qimg);
    ui->label->setPixmap(pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    this->setWindowTitle(QString("Babyphotoshop - %1 x %2 px")
                             .arg(currentImage.width)
                             .arg(currentImage.height));
}



