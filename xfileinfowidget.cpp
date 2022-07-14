/* Copyright (c) 2021-2022 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "xfileinfowidget.h"
#include "ui_xfileinfowidget.h"

XFileInfoWidget::XFileInfoWidget(QWidget *pParent) :
    XShortcutsWidget(pParent),
    ui(new Ui::XFileInfoWidget)
{
    ui->setupUi(this);

    g_pDevice=nullptr;
    g_nOffset=0;
    g_nSize=0;

    ui->checkBoxComment->setChecked(true);

    XOptions::setMonoFont(ui->plainTextEditFileInfo);

    // TODO load all strings
}

XFileInfoWidget::~XFileInfoWidget()
{
    delete ui;
}

void XFileInfoWidget::setData(QIODevice *pDevice, XBinary::FT fileType, QString sString, bool bAuto)
{
    this->g_pDevice=pDevice;
    g_nOffset=0;
    g_nSize=pDevice->size();

    if(this->g_nSize==-1)
    {
        this->g_nSize=(pDevice->size())-(this->g_nOffset);
    }

    XFormats::setFileTypeComboBox(fileType,g_pDevice,ui->comboBoxType);

    reloadType();

    if(bAuto)
    {
        reload();
    }
}

void XFileInfoWidget::reload()
{
    if(g_pDevice)
    {
        XFileInfo::OPTIONS options={};
        options.fileType=(XBinary::FT)(ui->comboBoxType->currentData().toInt());
    //    options.bShowAll=ui->checkBoxShowAll->isChecked();
        options.bComment=ui->checkBoxComment->isChecked();
        options.sString=(ui->comboBoxMethod->currentData().toString());

        XFileInfoModel *pModel=new XFileInfoModel;

        DialogXFileInfoProcess dip(XOptions::getMainWidget(this),g_pDevice,pModel,options);

        dip.showDialogDelay(1000);

        if(dip.isSuccess())
        {
            QString sText=pModel->toFormattedString();
    //        QString sText=XFileInfo::toCSV(pModel);

            ui->plainTextEditFileInfo->setPlainText(sText);
        }

        delete pModel;
    }
}

void XFileInfoWidget::registerShortcuts(bool bState)
{
    Q_UNUSED(bState)
    // TODO !!!
}

void XFileInfoWidget::on_pushButtonSave_clicked()
{
    QString sFileName=XBinary::getResultFileName(g_pDevice,QString("%1.txt").arg(tr("Info")));
    sFileName=QFileDialog::getSaveFileName(this,tr("Save file"),sFileName,QString("%1 (*.txt);;%2 (*)").arg(tr("Text files"),tr("All files")));

    if(!sFileName.isEmpty())
    {
        XOptions::savePlainTextEdit(ui->plainTextEditFileInfo,sFileName);
    }
}

void XFileInfoWidget::on_pushButtonReload_clicked()
{
    reload();
}

void XFileInfoWidget::on_checkBoxComment_toggled(bool bChecked)
{
    Q_UNUSED(bChecked)

    reload();
}

void XFileInfoWidget::on_comboBoxType_currentIndexChanged(int nIndex)
{
    Q_UNUSED(nIndex)

    reloadType();

    reload();
}

void XFileInfoWidget::on_comboBoxMethod_currentIndexChanged(int nIndex)
{
    Q_UNUSED(nIndex)

    reload();
}

void XFileInfoWidget::reloadType()
{
    XBinary::FT fileType=(XBinary::FT)(ui->comboBoxType->currentData().toInt());

    QList<XFileInfo::METHOD> listMethods=XFileInfo::getMethodNames(fileType);

#if QT_VERSION >= QT_VERSION_CHECK(5,3,0)
    const QSignalBlocker blocker(ui->comboBoxMethod);
#else
    const bool bBlocked1=ui->comboBoxMethod->blockSignals(true);
#endif

    qint32 nNumberOfMethods=listMethods.count();

    for(qint32 i=0;i<nNumberOfMethods;i++)
    {
        ui->comboBoxMethod->addItem(listMethods.at(i).sTranslated,listMethods.at(i).sName);
    }

#if QT_VERSION < QT_VERSION_CHECK(5,3,0)
    ui->comboBoxMethod->blockSignals(bBlocked1);
#endif
}
