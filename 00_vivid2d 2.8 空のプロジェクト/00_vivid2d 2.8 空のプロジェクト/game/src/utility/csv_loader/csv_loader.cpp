
/*!
 *  @file       csv_loader.cpp
 *  @brief      CSVローダー
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "csv_loader.h"
#include <fstream>
#include <sstream>

 /*
 *  コンストラクタ
 */
CCSVLoader::
CCSVLoader(void)
    : m_Cols(0)
    , m_Rows(0)
{
    m_Data.clear();
}

/*
 *  デストラクタ
 */
CCSVLoader::
~CCSVLoader(void)
{
}

/*
 *  CSVファイル読み込み
 */
void
CCSVLoader::
Load(const std::string& file_name)
{
    // 念のため解放する
    Unload();

    FILE* fp = nullptr;

    fopen_s(&fp, file_name.c_str(), "r");

    std::string item;

    char t = '\0';

    // 末尾まで順に調べる
    do
    {
        t = (char)fgetc(fp);

        if (t == ',')
        {
            m_Data.push_back(item);

            item.clear();
        }
        else if (t == '\n')
        {
            m_Data.push_back(item);

            item.clear();

            ++m_Rows;
        }
        else
        {
            item += t;
        }
    } while (t != EOF);

    fclose(fp);

    // 横に並んでいる数を算出
    m_Cols = (int)m_Data.size() / m_Rows;
}

/*
 *  解放
 */
void
CCSVLoader::
Unload(void)
{
    m_Data.clear();

    m_Cols = m_Rows = 0;
}

/*
 *  横に並んでいる数を取得
 */
int
CCSVLoader::
GetCols(void)
{
    return m_Cols;
}

/*
 *  縦に並んでいる数を取得
 */
int
CCSVLoader::
GetRows(void)
{
    return m_Rows;
}

/*
 *  データ数を取得
 */
int
CCSVLoader::
GetDataCount(void)
{
    return (int)m_Data.size();
}

/*
 *  指定されたデータを文字列で取得
 */
std::string
CCSVLoader::
GetString(int rows, int cols)
{
    return m_Data[(rows * m_Cols) + cols];
}

/*
 *  指定されたデータを整数に変換して取得
 */
int
CCSVLoader::
GetInteger(int rows, int cols)
{
    return stoi(m_Data[(rows * m_Cols) + cols]);

}

/*
 *  指定されたデータを実数に変換して取得
 */
float
CCSVLoader::
GetFloat(int rows, int cols)
{
    return stof(m_Data[(rows * m_Cols) + cols]);
}

bool CCSVLoader::GetBool(int rows, int cols)
{
    return static_cast<bool>(stoi(m_Data[(rows * m_Cols) + cols]));
}

void CCSVLoader::DeleteChara(int rows, int cols)
{
    m_Data[(rows * m_Cols) + cols].erase(m_Data[(rows * m_Cols) + cols].begin());

}
