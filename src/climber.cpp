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

    qDebug() << "Generated possible starts";

    foreach (ClimberState start, possibleStarts) {
        PathProblem problem(start, r.nGrips(), r.lastGrip());
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
        qDebug() << i;
        QList<ClimberState> arrangements;

        // assume lowest four are two hands and two feet, might need to swap them
        arrangements.append(ClimberState(i + 2, i + 3, i + 1, i));
        arrangements.append(ClimberState(i + 2, i + 3, i, i + 1));
        arrangements.append(ClimberState(i + 3, i + 2, i, i + 1));
        arrangements.append(ClimberState(i + 2, i + 3, i + 1, i));

        // hands match
        arrangements.append(ClimberState(i + 2, i + 2, i + 1, i));
        arrangements.append(ClimberState(i + 3, i + 3, i + 1, i));

        for (int j = 0; j < arrangements.length(); ++j)
            if (_engine->isPossible(arrangements[j]) && _engine->isReachableStart(arrangements[j]))
                 foreach (ClimberState s, _engine->configurations(arrangements[j]))
                     feasibleStarts.append(s);

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
        Mat stateViewer = r.imgCopy();
        Q_ASSERT(stateViewer.data);

        drawState(stateViewer, r, p[i]);
        QString imgName("Move");
        imgName.append(QString::number(i));

        jug::showImage(&stateViewer, imgName.toStdString(), true);
    }
}

void Climber::drawState(cv::Mat &img, const Route &r, const ClimberState s) const
{
    for (int i = 0; i < N_LIMBS; ++i) {
        int gripIndex = s.getGrip((Limb) i);
        if (gripIndex != -1) {
            Q_ASSERT(gripIndex < r.nGrips());
            vector<Contour> contourWrapper(1, r[gripIndex]->getContour());
            drawContours(img, contourWrapper, 0, limbColors[i], 2);
        }
    }
}
