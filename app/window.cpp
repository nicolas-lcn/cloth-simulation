/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "glwidget.h"
#include "window.h"
#include "mainwindow.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QGuiApplication>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>

Window::Window(MainWindow *mw)
    : mainWindow(mw)
{
    glWidget = new GLWidget;
    glWidget->setAttribute(Qt::WA_DeleteOnClose, true);
    mainWindow->setFixedSize(1000, 1000);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(glWidget);

    QWidget *w = new QWidget;
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->setLayout(container);
    w->setFixedSize(900,800);
    mainLayout->addWidget(w, 0, Qt::AlignCenter);
    mainLayout->setContentsMargins(25, 25, 25, 25);

    resetBtn = new QPushButton(tr("Reset"), this);
    connect(resetBtn, &QPushButton::clicked, this, &Window::resetSimulation);
    setLayout(mainLayout);

    QVBoxLayout *sliders = new QVBoxLayout;
    mainLayout->addLayout(sliders);

    QLabel *springConstantLabel = new QLabel("Spring Constant");
    QSlider *springConstantSlider = new QSlider(Qt::Horizontal);
    springConstantSlider->setRange(0, 100);
    springConstantSlider->setSingleStep(5);
    springConstantSlider->setPageStep(5);
    springConstantSlider->setTickInterval(5);
    springConstantSlider->setTickPosition(QSlider::TicksRight);

    QLabel *dampingConstantLabel = new QLabel("Damping Constant");
    QSlider *dampingConstantSlider = new QSlider(Qt::Horizontal);
    dampingConstantSlider->setRange(0, 100);
    dampingConstantSlider->setSingleStep(5);
    dampingConstantSlider->setPageStep(5);
    dampingConstantSlider->setTickInterval(5);
    dampingConstantSlider->setTickPosition(QSlider::TicksRight);

    sliders->addWidget(springConstantLabel, 1, Qt::AlignTop);
    sliders->addWidget(springConstantSlider, 0, Qt::AlignTop);
    sliders->addWidget(dampingConstantLabel, 1, Qt::AlignTop);
    sliders->addWidget(dampingConstantSlider, 0, Qt::AlignTop);

    connect(springConstantSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setSpringConstant(int)));
    connect(glWidget, SIGNAL(springConstantChanged(int)), springConstantSlider, SLOT(setValue(int)));
    connect(dampingConstantSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setDampingConstant(int)));
    connect(glWidget, SIGNAL(dampingConstantChanged(int)), dampingConstantSlider, SLOT(setValue(int)));

    springConstantSlider->setValue(100);
    dampingConstantSlider->setValue(100);
    setWindowTitle(tr("Simulation"));
}


void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        QCoreApplication::quit();
    else
        glWidget->keyPressEvent(e);
}

void Window::dockUndock()
{
    if (parent()) {
        setParent(0);
        setAttribute(Qt::WA_DeleteOnClose);
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int width =screenGeometry.width();
        int height = screenGeometry.height();
        move(width / 2 - this->width() / 2,
             height / 2 - this->height() / 2);
        //dockBtn->setText(tr("Dock"));
        show();
    } else {
        if (!mainWindow->centralWidget()) {
            if (mainWindow->isVisible()) {
                setAttribute(Qt::WA_DeleteOnClose, true);
                dockBtn->setText(tr("Undock"));
                mainWindow->setCentralWidget(this);
            } else {
                QMessageBox::information(0, tr("Cannot dock"), tr("Main window already closed"));
            }
        } else {
            QMessageBox::information(0, tr("Cannot dock"), tr("Main window already occupied"));
        }
    }
}

void Window::resetSimulation()
{
    glWidget->resetSimulation();
}




