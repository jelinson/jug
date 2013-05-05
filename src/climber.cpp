#include "climber.h"

using namespace cv;

const QList<Scalar> Climber::limbColors = QList<Scalar>()
        << Scalar(0, 0, 255)
        << Scalar(0, 255, 0)
        << Scalar(255, 0, 0)
        << Scalar(255, 255, 255);

Climber::Climber(Physics *engine, const ClimberSpecs &specs)
    : _engine(engine), _specs(specs)
{
    _engine->loadClimber(_specs);
}

void Climber::setSpecs(const ClimberSpecs &specs)
{
    _specs = specs;
}

void Climber::setEngine(Physics *engine)
{
    _engine = engine;
}

Path Climber::climb(const Route &r, bool visualize) const
{
    Q_ASSERT(r.nGrips() > N_LIMBS);

    _engine->loadRoute(&r);
    QList<ClimberState> possibleStarts = start(r);

    if (!possibleStarts.empty())
        qDebug() << "Generated possible starts";

    foreach (ClimberState start, possibleStarts) {
        qDebug() << "Trying to start from" << start;
        PathProblem problem(start, r.nGrips(), r.lastGrip());
        problem.setEngine(_engine);

        Path solution =  Searcher::bfs(problem);
        if (!solution.isEmpty()) {
            if (visualize)
                visualizePath(r, solution);
            return solution;
        }
    }

    qDebug() << "Could not find a solution";
    return Path();
}

QList<ClimberState> Climber::start(const Route &r) const
{
    int i = 0;
    QList<ClimberState> feasibleStarts;
    qDebug() << "Number of grips" << r.nGrips();
    while (i < r.nGrips() - 3) {
        QList<ClimberState> arrangements;

        // assume lowest four are two hands and two feet, might need to swap them
        arrangements.append(ClimberState(i + 2, i + 3, i + 1, i));
        arrangements.append(ClimberState(i + 2, i + 3, i, i + 1));
        arrangements.append(ClimberState(i + 3, i + 2, i, i + 1));
        arrangements.append(ClimberState(i + 2, i + 3, i + 1, i));

        // hands match
        arrangements.append(ClimberState(i + 2, i + 2, i + 1, i));
        arrangements.append(ClimberState(i + 2, i + 2, i, i + 1));
        arrangements.append(ClimberState(i + 3, i + 3, i + 1, i));
        arrangements.append(ClimberState(i + 3, i + 3, i, i + 1));

        for (int j = 0; j < arrangements.length(); ++j) {
            qDebug() << "Testing" << arrangements[j];
            visualizeState(r, arrangements[j]);
            if (_engine->isPossible(arrangements[j]) && _engine->isReachableStart(arrangements[j]))
                 foreach (ClimberState s, _engine->configurations(arrangements[j]))
                     feasibleStarts.append(s);
        }
        jug::clearImages();

        if (!feasibleStarts.empty())
            return feasibleStarts;

        ++i;
    }
    qDebug() << "No feasible start position found";
    return QList<ClimberState>();
}

void Climber::visualizePath(const Route &r, const Path &p) const
{
    for (int i = 0; i < p.size(); ++i) {
        qDebug() << "Move" << i << p[i];
        visualizeState(r, p[i], i);
    }
}

void Climber::visualizeState(const Route &r, const ClimberState &pos, int index) const
{
    Mat stateViewer = r.imgCopy();
    Q_ASSERT(stateViewer.data);

    drawState(stateViewer, r, pos);
    QString imgName("Move");
    imgName.append(QString::number(index));

    jug::showImage(&stateViewer, imgName.toStdString(), true);
}

void Climber::drawState(cv::Mat &img, const Route &r, const ClimberState s) const
{
    for (int i = 0; i < N_LIMBS; ++i) {
        int gripIndex = s.getGripIndex((Limb) i);
        if (gripIndex != -1) {
            Q_ASSERT(gripIndex < r.nGrips());
            vector<Contour> contourWrapper(1, r[gripIndex]->getContour());
            drawContours(img, contourWrapper, 0, limbColors[i], 2);
        }
    }

    if (s.getCom().x != -1)
        circle(img, s.getCom(), 7, Scalar(0,0,0), -1);
    else
        circle(img, _engine->geometricCenter(s), 7, Scalar(0,0,0), -1);

    rectangle(img, Rect(0, IMG_HEIGHT - 12, IMG_WIDTH, 12), Scalar(255, 255, 255), -1);

    putText(img, "Black=COM, Blue=RL, White=LL, Red=LA, Green=RA",
            Point(0, IMG_HEIGHT - 2), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0), 1);
}
