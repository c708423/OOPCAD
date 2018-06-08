#include "../include/Editor.h"
#include <queue>
#include <algorithm>
using namespace std;
using namespace ACCAD;

inline bool IsInside(const Vec2i& pixel, const Image& image)
{
    return (0 <= pixel.x && pixel.x < image.getWidth()) && (0 <= pixel.y && pixel.y < image.getHeight());
}

float DistanceToLine(const Vec2i& P, const Vec2i& A, const Vec2i& B)
{
    auto BA = A - B;
    int sqr_len = BA.sqrLength();
    if (sqr_len == 0.0)
        return (P - A).length();
    float t = max(0, min(1, dot(P - A, B - A) / sqr_len));
    Vec2 projection = Vec2(A) + Vec2(B - A)*t;
    return (Vec2(P) - projection).length();
}

void ACCAD::Editor::startDraw()
{
    strokeManager.startDraw();
}

void ACCAD::Editor::finishDraw()
{
    Stroke* stroke = strokeManager.finishDraw();
    if (stroke != nullptr)
    {
        stack.pushback(stroke);
    }
}

void ACCAD::Editor::movePen(const Vec2i & from, const Vec2i & to)
{
    static
    unordered_set<Vec2i> hashtable;
    queue<Vec2i> queue;

    queue.push(from);
    hashtable.insert(from);
    while (!queue.empty())
    {
        auto center = queue.front();
        queue.pop();
        for (auto d : delta)
        {
            Vec2i point(center.x + d[0], center.y + d[1]);
            //�ڱ߽���&&����δ������&&����С�ڻ��ʿ���
            if (image.isInside(point) && hashtable.find(point) == hashtable.end() && DistanceToLine(point, from, to) <= pen.width / 2)
            {
                queue.push(point);
                hashtable.insert(point);
                strokeManager.addPixel(point, image.at(point), pen.color);
            }
        }
    }
    //TODO������ˢ��һ�Σ�
}

void ACCAD::Editor::setPen(const Pen & pen)
{
    this->pen = pen;
}

Pen ACCAD::Editor::getPen()
{
    return this->pen;
}

void ACCAD::Editor::startAlter(MouseButton mouse)
{
    AlterManager::AlterMode alterMode;
    switch (mouse)
    {
    case ACCAD::Editor::Left:
        alterMode = AlterManager::Move;
        break;
    case ACCAD::Editor::Right:
        alterMode = AlterManager::Vertex;
        break;
    default:
        alterMode = AlterManager::Move;
        break;
    }
    alterManager.startAlter(selectedIndex, alterMode);
}

void ACCAD::Editor::finishAlter()
{
    Alternation* alter = alterManager.finishAlter();
    if (alter != nullptr)
    {
        stack.pushback(alter);
    }
}

void ACCAD::Editor::AlterFigure(const Vec2i & from, const Vec2i & to)
{
    alterManager.AlterFigure(from, to);
}

void ACCAD::Editor::setAlterMode(const Vec2i & point, MouseButton mouse)
{
    //������ʽ��
    //�����
    //  8��ê��ΪԲ�ĵ�8��Բ������
    //  4�����ⲿ������������ת
    //  ͼ���ڲ����ƶ�
    //�Ҽ���
    //  �����ָ�������ƶ�
    switch (mouse)
    {
    case MouseButton::Left:
        break;
    case MouseButton::Right:
        break;
    default:
        break;
    }
}

int ACCAD::Editor::SelectFigure(const Vec2i & point)
{
    //������������ѡ��ͼ��
    return 0;
}