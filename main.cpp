#include <QApplication>
#include <QUrl>
#include <QAudioOutput>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QPushButton>
#include <QGridLayout>
#include <QList>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    int n = 0;
    QWidget *b = new QWidget;
    auto l = new QGridLayout;
    auto player = new QMediaPlayer;
    QList<QString> list = {"/home/student/untitled11/Download.mp4", "/home/student/untitled11/otkrytka-3413.mp4", "/home/student/untitled11/Download (1-я копия).mp4"};
    player->setSource(QUrl::fromLocalFile(list[0]));
    auto videoWidget = new QVideoWidget;
    player->setVideoOutput(videoWidget);
    l->addWidget(videoWidget);
    auto *stop = new QPushButton("||", b);
    QObject::connect(stop, &QPushButton::clicked, [&](){
        if (player->playbackState() == QMediaPlayer::PlayingState) {
            player->pause();
            stop->setText(">");
        }
        else if (player->playbackState() == QMediaPlayer::PausedState) {
            player->play();
            stop->setText("||");
        }
    });
    auto *plus = new QPushButton("+5", b);
    auto *min = new QPushButton("-5", b);
    QObject::connect(plus, &QPushButton::clicked, [&](){
        player->setPosition(player->position() + 5000);
    });
    QObject::connect(min, &QPushButton::clicked, [&](){
        player->setPosition(player->position() - 5000);
    });
    QObject::connect(player, &QMediaPlayer::mediaStatusChanged, [player](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            player->setPosition(0);
            player->play();
        }
    });
    auto *lay = new QLabel("Лайки: 0", b);
    auto *like = new QPushButton("like", b);
    bool likes = 0;
    QObject::connect(like, &QPushButton::clicked, [&](){
        if(likes){
            lay->setText("Лайки: 0");
        }
        else{
            lay->setText("Лайки: 1");
        }
        likes = !likes;
    });
    auto *next = new QPushButton("->",b);
    auto *perv = new QPushButton("<-",b);
    QObject::connect(next, &QPushButton::clicked, [&](){
        n++;
        if(n==list.length()){
            n=0;
        }
        player->setSource(QUrl::fromLocalFile(list[n]));
        player->play();
    });
    QObject::connect(perv, &QPushButton::clicked, [&](){
        n--;
        if(n==-1){
            n=list.length()-1;
        }
        player->setSource(QUrl::fromLocalFile(list[n]));
        player->play();
    });
    l->addWidget(lay);
    l->addWidget(stop);
    l->addWidget(like);
    l->addWidget(plus);
    l->addWidget(min);
    l->addWidget(next);
    l->addWidget(perv);
    b->setLayout(l);
    player->play();
    b->resize(800, 600);
    b->show();
    return a.exec();
}

