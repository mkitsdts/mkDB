#include "datapage.h"
#include <sstream>
#include <fstream>

DataPage::DataPage() : dirty(0), key_column(0), current_column(0), column_count(0), buffer{ 0 }, directory{}, header{}, page_header{}, tailer{}
{
}

DataPage::~DataPage()
{
}

DataPage* DataPage::create(unsigned char order)
    
{
    auto page = new DataPage;
    page->header.FILE_PAGE_ORDER = order;
    return page;
}

void DataPage::add_column(char type, std::string &column_name, char is_key, char is_null)
{
    column_information column{};
    column.COLUMN_TYPE = type;
    column.COLUMN_NAME = const_cast<char*>(column_name.data());
    column.COLUMN_KEY = is_key;
    column.COLUMN_NULL = is_null;
    columns.push_back(column);
}

void DataPage::add_column(char type, std::string &&column_name, char is_key, char is_null)
{
    column_information column{};
    column.COLUMN_TYPE = type;
    column.COLUMN_NAME = const_cast<char*>(column_name.data());
    column.COLUMN_KEY = is_key;
    column.COLUMN_NULL = is_null;
    columns.push_back(column);
}

bool DataPage::drop_column(std::string &column_name)
{
    for (auto iter = columns.begin(); iter != columns.end(); ++iter)
    {
        if (iter->COLUMN_NAME == column_name)
        {
            columns.erase(iter);
            return 0;
        }
    }
    return -1;
}

bool DataPage::drop_column(std::string &&column_name)
{
    for (auto iter = columns.begin(); iter != columns.end(); ++iter)
    {
        if (iter->COLUMN_NAME == column_name)
        {
            columns.erase(iter);
            return 0;
        }
    }
    return -1;
}

bool DataPage::select_column(std::string &column_name)
{
    for (auto iter = columns.begin(); iter != columns.end(); ++iter)
    {
        if (iter->COLUMN_NAME == column_name)
        {
            current_column = iter - columns.begin();
            return 0;
        }
    }
    return -1;
}

bool DataPage::select_column(std::string &&column_name)
{
    for (auto iter = columns.begin(); iter != columns.end(); ++iter)
    {
        if (iter->COLUMN_NAME == column_name)
        {
            current_column = iter - columns.begin();
            return 0;
        }
    }
    return -1;
}

bool DataPage::select_column(unsigned char column_order)
{
    if (column_order < columns.size())
    {
        current_column = column_order;
        return 0;
    }
    return -1;
}

bool DataPage::read(int page_order)
{
    std::ifstream file;
    file.open(PAGE_PATH, std::ios::out | std::ios::binary);
    if (!file.is_open())
        return -1;
    
    file.seekg(PAGE_SIZE * page_order, std::ios::beg);
    file.read(buffer, PAGE_SIZE);
    file.close();
    parse_data();
    return 0;
}

bool DataPage::write()
{
    std::ofstream file;
    file.open(PAGE_PATH, std::ios::out | std::ios::binary);
    if (!file.is_open())
    {
		printf("open file failed\n");
        return -1;
    }

    file.seekp(PAGE_SIZE * header.FILE_PAGE_ORDER, std::ios::beg);
    add_to_buffer();
    file.write(buffer, PAGE_SIZE);
    file.close();
    return 0;
}

bool DataPage::parse_data()
{
    // 解析文件头
    header.FILE_PAGE_SPACE_OR_CHECKSUM = toInt(buffer[0], buffer[1], buffer[2], buffer[3]);
    header.FILE_PAGE_ORDER = buffer[4];
    header.FILE_PAGE_PREV = buffer[5];
    header.FILE_PAGE_NEXT = buffer[6];
    header.FILE_PAGE_LSN.FILE_PAGE_LSN_OFFSET = toInt(buffer[7], buffer[8], buffer[9], buffer[10]);
    header.FILE_PAGE_LSN.FILE_PAGE_LSN_CHECKSUM = toInt(buffer[11], buffer[12], buffer[13], buffer[14]);

    // 解析页面头
    page_header.PAGE_N_DIR_DATA = toInt(buffer[15], buffer[16], buffer[17], buffer[18]);
    page_header.PAGE_HEAP_TOP = toInt(buffer[19], buffer[20], buffer[21], buffer[22]);
    page_header.PAGE_LAST_INSERT = toInt(buffer[23], buffer[24], buffer[25], buffer[26]);
    page_header.PAGE_RECORD_NUMBER = toInt(buffer[27], buffer[28], buffer[29], buffer[30]);

    // 解析页目录
    directory.max_key = toInt(buffer[31], buffer[32], buffer[33], buffer[34]);
    directory.min_key = toInt(buffer[35], buffer[36], buffer[37], buffer[38]);

    // 解析列信息
    column_count = toInt(buffer[39], buffer[40], buffer[41], buffer[42]);
    key_column = buffer[43];

    uint32_t offset = 44;
    for(uint32_t i = 0; i < column_count; ++i)
    {
        column_information column{};
        // 将字节信息转换为位信息
        column.assign(buffer[offset]);

        column.COLUMN_KEY = toInt(buffer[offset + 1], buffer[offset + 2], buffer[offset + 3], buffer[offset + 4]);
        if(column.COLUMN_TYPE == VARCHAR)
            column.COLUMN_NAME_LENGTH = buffer[offset + 5];
        else
            column.COLUMN_NAME_LENGTH = -1;

        column.COLUMN_NAME = new char[column.COLUMN_NAME_LENGTH];
        for (int j = 0; j < column.COLUMN_NAME_LENGTH; ++j)
        {
            column.COLUMN_NAME[j] = buffer[offset + 6 + j];
        }
        // 计算偏移量
        offset += (6 + column.COLUMN_NAME_LENGTH);

        columns.push_back(column);
    }

    // 解析行信息
    for(int i = 0; i < page_header.PAGE_RECORD_NUMBER; ++i)
    {
        user_records record;
        std::vector<std::string> tmp;
        for(int j = 0; j < column_count; ++j)
        {
            switch (columns[j].COLUMN_TYPE)
            {
            case INT:
            {
                tmp.push_back(std::to_string(toInt(buffer[offset], buffer[offset + 1], buffer[offset + 2], buffer[offset + 3])));
                offset += 4;
                break;
            }
            case FLOAT:
            {
                tmp.push_back(std::to_string(toFloat(buffer[offset], buffer[offset + 1], buffer[offset + 2], buffer[offset + 3])));
                offset += 4;
                break;
            }
            case VARCHAR:
            {
                int length = toInt(buffer[offset], buffer[offset + 1], buffer[offset + 2], buffer[offset + 3]);
                offset += 4;
                std::string str;
                for (int k = 0; k < length; ++k)
                {
                    str.push_back(buffer[offset + k]);
                }
                tmp.push_back(str);
                offset += length;
                break;
            }
            case DATE:
            {
                tmp.push_back(to_date(buffer[offset], buffer[offset + 1], buffer[offset + 2], buffer[offset + 3]));
                offset += 4;
                break;
            }
            default:
            {
                break;
            }
            }
        }
    }

    // 解析文件尾
    tailer.FILE_PAGE_CHECKSUM = toInt(buffer[4092], buffer[4093], buffer[4094], buffer[4095]);
    return 0;
}

bool DataPage::add_to_buffer()
{
    if(header.FILE_PAGE_SPACE_OR_CHECKSUM <= 0)
        return -1;
    // 添加文件头
    buffer[0] = (header.FILE_PAGE_SPACE_OR_CHECKSUM >> 24) & 0xFF;
    buffer[1] = (header.FILE_PAGE_SPACE_OR_CHECKSUM >> 16) & 0xFF;
    buffer[2] = (header.FILE_PAGE_SPACE_OR_CHECKSUM >> 8) & 0xFF;
    buffer[3] = header.FILE_PAGE_SPACE_OR_CHECKSUM & 0xFF;
    buffer[4] = header.FILE_PAGE_ORDER;
    buffer[5] = header.FILE_PAGE_PREV;
    buffer[6] = header.FILE_PAGE_NEXT;
    buffer[7] = (header.FILE_PAGE_LSN.FILE_PAGE_LSN_OFFSET >> 24) & 0xFF;
    buffer[8] = (header.FILE_PAGE_LSN.FILE_PAGE_LSN_OFFSET >> 16) & 0xFF;
    buffer[9] = (header.FILE_PAGE_LSN.FILE_PAGE_LSN_OFFSET >> 8) & 0xFF;
    buffer[10] = header.FILE_PAGE_LSN.FILE_PAGE_LSN_OFFSET & 0xFF;
    buffer[11] = (header.FILE_PAGE_LSN.FILE_PAGE_LSN_CHECKSUM >> 24) & 0xFF;
    buffer[12] = (header.FILE_PAGE_LSN.FILE_PAGE_LSN_CHECKSUM >> 16) & 0xFF;
    buffer[13] = (header.FILE_PAGE_LSN.FILE_PAGE_LSN_CHECKSUM >> 8) & 0xFF;
    buffer[14] = header.FILE_PAGE_LSN.FILE_PAGE_LSN_CHECKSUM & 0xFF;

    // 添加页面头
    buffer[15] = (page_header.PAGE_N_DIR_DATA >> 24) & 0xFF;
    buffer[16] = (page_header.PAGE_N_DIR_DATA >> 16) & 0xFF;
    buffer[17] = (page_header.PAGE_N_DIR_DATA >> 8) & 0xFF;
    buffer[18] = page_header.PAGE_N_DIR_DATA & 0xFF;
    buffer[19] = (page_header.PAGE_HEAP_TOP >> 24) & 0xFF;
    buffer[20] = (page_header.PAGE_HEAP_TOP >> 16) & 0xFF;
    buffer[21] = (page_header.PAGE_HEAP_TOP >> 8) & 0xFF;
    buffer[22] = page_header.PAGE_HEAP_TOP & 0xFF;
    buffer[23] = (page_header.PAGE_LAST_INSERT >> 24) & 0xFF;
    buffer[24] = (page_header.PAGE_LAST_INSERT >> 16) & 0xFF;
    buffer[25] = (page_header.PAGE_LAST_INSERT >> 8) & 0xFF;
    buffer[26] = page_header.PAGE_LAST_INSERT & 0xFF;
    buffer[27] = (page_header.PAGE_RECORD_NUMBER >> 24) & 0xFF;
    buffer[28] = (page_header.PAGE_RECORD_NUMBER >> 16) & 0xFF;
    buffer[29] = (page_header.PAGE_RECORD_NUMBER >> 8) & 0xFF;
    buffer[30] = page_header.PAGE_RECORD_NUMBER & 0xFF;

    // 添加页目录
    buffer[31] = (directory.max_key >> 24) & 0xFF;
    buffer[32] = (directory.max_key >> 16) & 0xFF;
    buffer[33] = (directory.max_key >> 8) & 0xFF;
    buffer[34] = directory.max_key & 0xFF;
    buffer[35] = (directory.min_key >> 24) & 0xFF;
    buffer[36] = (directory.min_key >> 16) & 0xFF;
    buffer[37] = (directory.min_key >> 8) & 0xFF;
    buffer[38] = directory.min_key & 0xFF;
    
    // 添加列信息
    buffer[39] = (column_count >> 24) & 0xFF;
    buffer[40] = (column_count >> 16) & 0xFF;
    buffer[41] = (column_count >> 8) & 0xFF;
    buffer[42] = column_count & 0xFF;   
    buffer[43] = key_column;

    int offset = 44;
    for(int i = 0; i < column_count; ++i)
    {
        buffer[offset] = columns[i].toChar();

        buffer[offset + 1] = (columns[i].COLUMN_KEY >> 24) & 0xFF;
        buffer[offset + 2] = (columns[i].COLUMN_KEY >> 16) & 0xFF;
        buffer[offset + 3] = (columns[i].COLUMN_KEY >> 8) & 0xFF;
        buffer[offset + 4] = columns[i].COLUMN_KEY & 0xFF;

        if(columns[i].COLUMN_TYPE == VARCHAR)
        {
            buffer[offset + 5] = (columns[i].COLUMN_NAME_LENGTH >> 24) & 0xFF;
            buffer[offset + 6] = (columns[i].COLUMN_NAME_LENGTH >> 16) & 0xFF;
            buffer[offset + 7] = (columns[i].COLUMN_NAME_LENGTH >> 8) & 0xFF;
            buffer[offset + 8] = columns[i].COLUMN_NAME_LENGTH & 0xFF;
            for (int j = 0; j < columns[i].COLUMN_NAME_LENGTH; ++j)
            {
                buffer[offset + 9 + j] = columns[i].COLUMN_NAME[j];
            }
            offset += (9 + columns[i].COLUMN_NAME_LENGTH);
        }
    }

    // 添加行信息
    for(int i = 0; i < page_header.PAGE_RECORD_NUMBER; ++i)
    {
        for(int j = 0; j < column_count; ++j)
        {
            switch (columns[j].COLUMN_TYPE)
            {
            case INT:
            {
				int value = std::stoi(data[i].values[j]);
				buffer[offset] = (value >> 24) & 0xFF;
				buffer[offset + 1] = (value >> 16) & 0xFF;
				buffer[offset + 2] = (value >> 8) & 0xFF;
				buffer[offset + 3] = value & 0xFF;
                offset += 4;
                break;
            }
            case FLOAT:
            {
				float value = std::stof(data[i].values[j]);
				int tmp = *(int*)&value;
				buffer[offset] = (tmp >> 24) & 0xFF;
				buffer[offset + 1] = (tmp >> 16) & 0xFF;
				buffer[offset + 2] = (tmp >> 8) & 0xFF;
				buffer[offset + 3] = tmp & 0xFF;
                offset += 4;
                break;
            }
            case VARCHAR:
            {
				for (int k = 0; k < data[i].values[j].size(); ++k)
                {
                    buffer[offset + k] = data[i].values[j][k];
                }
				offset += data[i].values[j].size();
                break;
            }
            case DATE:
            {
                for (int k = 0; k < data[i].values[j].size(); ++k)
                {
					buffer[offset + k] = data[i].values[j][k];
                }
                offset += data[i].values[j].size();
                break;
            }
            default:
            {
                break;
            }
            }
        }
    // 添加文件尾
    buffer[4092] = (tailer.FILE_PAGE_CHECKSUM >> 24) & 0xFF;
    buffer[4093] = (tailer.FILE_PAGE_CHECKSUM >> 16) & 0xFF;
    buffer[4094] = (tailer.FILE_PAGE_CHECKSUM >> 8) & 0xFF;
    buffer[4095] = tailer.FILE_PAGE_CHECKSUM & 0xFF;
    return 0;
    }
}