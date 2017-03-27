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

#include "HighLighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;
    preprocessFormat.setForeground(QColor(255,165,0));
    preprocessFormat.setFontWeight(QFont::Bold);
    QStringList preprocessPatterns;
    preprocessPatterns << "^#ALIAS\\b" << "^#UNALIAS\\b" << "^#IMPORT\\b"
                    << "^#DEFINEMACRO\\b" << "^#ENDMACRO\\b" << "^#MERGE\\b" << "^#DATA\\b";
    foreach (const QString &pattern, preprocessPatterns) {
        rule.pattern = QRegExp(pattern,Qt::CaseInsensitive);
        rule.format = preprocessFormat;
        highlightingRules.append(rule);
    }


    conditionFormat.setForeground(Qt::magenta);
    conditionFormat.setFontWeight(QFont::Bold);
    QStringList conditionPatterns;
    conditionPatterns << "\\bAL\\b" << "\\bEQ\\b" << "\\bNE\\b"
                    << "\\bCS\\b" << "\\bCC\\b" << "\\bMI\\b"
                    << "\\bPL\\b" << "\\bVS\\b" << "\\bVC\\b"
                    << "\\bDZ\\b" << "\\bNZ\\b" << "\\bLE\\b"
                    << "\\bGE\\b" << "\\bLT\\b" << "\\bGT\\b"
                    << "\\bUN\\b" ;
    foreach (const QString &pattern, conditionPatterns) {
        rule.pattern = QRegExp(pattern, Qt::CaseInsensitive);
        rule.format = conditionFormat;
        highlightingRules.append(rule);
    }

    labelFormat.setFontWeight(QFont::Bold);
    labelFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("^.*:");
    rule.format = labelFormat;
    highlightingRules.append(rule);


    immediateFormat.setForeground(Qt::cyan);
    rule.pattern = QRegExp("(#(0b|0B)[0-1]+\\b)|(#(0X|0x)[0-9A-Fa-f]+\\b)|((^|\\s)[0-9]+\\b)");
    rule.format = immediateFormat;
    highlightingRules.append(rule);

    registerFormat.setForeground(Qt::darkCyan);
    rule.pattern = QRegExp("\\b(R([0-9]|[1-2][0-9]|3[0-1]))|(I[0-9])|(F[0-9])|LR|BP|PC|SP|(V[0-7])|(VI[0-3])|(VF[0-3])\\b");
    rule.format = registerFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::green);
    rule.pattern = QRegExp(";[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);
/*     functionFormat.setFontItalic(true); */
    // functionFormat.setForeground(Qt::blue);
    // rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    // rule.format = functionFormat;
    /* highlightingRules.append(rule); */

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
