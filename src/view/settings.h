#ifndef CPP4_3DVIEWER_V2_0_SRC_VIEW_SETTINGS_H_
#define CPP4_3DVIEWER_V2_0_SRC_VIEW_SETTINGS_H_
#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>


namespace s21 {
class Settings {
    public:
        Settings();
        void SaveSettings();
        void GetSettings();
        QColor line_color;
        QColor back_color;
        QColor vertex_color;
        bool projection_orth;
        int vertex_type;
        int line_type;
        float line_width = 0.01;
        float vertex_size = 0.01;

};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_SRC_VIEW_SETTINGS_H_
