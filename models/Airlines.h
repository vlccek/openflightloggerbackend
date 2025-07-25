/**
 *
 *  Airlines.h
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#pragma once
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/BaseBuilder.h>
#ifdef __cpp_impl_coroutine
#include <drogon/orm/CoroMapper.h>
#endif
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>
#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

namespace drogon
{
namespace orm
{
class DbClient;
using DbClientPtr = std::shared_ptr<DbClient>;
}
}
namespace drogon_model
{
namespace mydatabase
{

class Airlines
{
  public:
    struct Cols
    {
        static const std::string _airline_id;
        static const std::string _name;
        static const std::string _alias;
        static const std::string _iata_code;
        static const std::string _icao_code;
        static const std::string _callsign;
        static const std::string _country;
        static const std::string _active;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = int32_t;
    const PrimaryKeyType &getPrimaryKey() const;

    /**
     * @brief constructor
     * @param r One row of records in the SQL query result.
     * @param indexOffset Set the offset to -1 to access all columns by column names,
     * otherwise access all columns by offsets.
     * @note If the SQL is not a style of 'select * from table_name ...' (select all
     * columns by an asterisk), please set the offset to -1.
     */
    explicit Airlines(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit Airlines(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    Airlines(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    Airlines() = default;

    void updateByJson(const Json::Value &pJson) noexcept(false);
    void updateByMasqueradedJson(const Json::Value &pJson,
                                 const std::vector<std::string> &pMasqueradingVector) noexcept(false);
    static bool validateJsonForCreation(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForCreation(const Json::Value &,
                                                const std::vector<std::string> &pMasqueradingVector,
                                                    std::string &err);
    static bool validateJsonForUpdate(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForUpdate(const Json::Value &,
                                          const std::vector<std::string> &pMasqueradingVector,
                                          std::string &err);
    static bool validJsonOfField(size_t index,
                          const std::string &fieldName,
                          const Json::Value &pJson,
                          std::string &err,
                          bool isForCreation);

    /**  For column airline_id  */
    ///Get the value of the column airline_id, returns the default value if the column is null
    const int32_t &getValueOfAirlineId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getAirlineId() const noexcept;
    ///Set the value of the column airline_id
    void setAirlineId(const int32_t &pAirlineId) noexcept;

    /**  For column name  */
    ///Get the value of the column name, returns the default value if the column is null
    const std::string &getValueOfName() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getName() const noexcept;
    ///Set the value of the column name
    void setName(const std::string &pName) noexcept;
    void setName(std::string &&pName) noexcept;

    /**  For column alias  */
    ///Get the value of the column alias, returns the default value if the column is null
    const std::string &getValueOfAlias() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getAlias() const noexcept;
    ///Set the value of the column alias
    void setAlias(const std::string &pAlias) noexcept;
    void setAlias(std::string &&pAlias) noexcept;
    void setAliasToNull() noexcept;

    /**  For column iata_code  */
    ///Get the value of the column iata_code, returns the default value if the column is null
    const std::string &getValueOfIataCode() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getIataCode() const noexcept;
    ///Set the value of the column iata_code
    void setIataCode(const std::string &pIataCode) noexcept;
    void setIataCode(std::string &&pIataCode) noexcept;
    void setIataCodeToNull() noexcept;

    /**  For column icao_code  */
    ///Get the value of the column icao_code, returns the default value if the column is null
    const std::string &getValueOfIcaoCode() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getIcaoCode() const noexcept;
    ///Set the value of the column icao_code
    void setIcaoCode(const std::string &pIcaoCode) noexcept;
    void setIcaoCode(std::string &&pIcaoCode) noexcept;
    void setIcaoCodeToNull() noexcept;

    /**  For column callsign  */
    ///Get the value of the column callsign, returns the default value if the column is null
    const std::string &getValueOfCallsign() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getCallsign() const noexcept;
    ///Set the value of the column callsign
    void setCallsign(const std::string &pCallsign) noexcept;
    void setCallsign(std::string &&pCallsign) noexcept;
    void setCallsignToNull() noexcept;

    /**  For column country  */
    ///Get the value of the column country, returns the default value if the column is null
    const std::string &getValueOfCountry() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getCountry() const noexcept;
    ///Set the value of the column country
    void setCountry(const std::string &pCountry) noexcept;
    void setCountry(std::string &&pCountry) noexcept;

    /**  For column active  */
    ///Get the value of the column active, returns the default value if the column is null
    const bool &getValueOfActive() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<bool> &getActive() const noexcept;
    ///Set the value of the column active
    void setActive(const bool &pActive) noexcept;


    static size_t getColumnNumber() noexcept {  return 8;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;
    /// Relationship interfaces
  private:
    friend drogon::orm::Mapper<Airlines>;
    friend drogon::orm::BaseBuilder<Airlines, true, true>;
    friend drogon::orm::BaseBuilder<Airlines, true, false>;
    friend drogon::orm::BaseBuilder<Airlines, false, true>;
    friend drogon::orm::BaseBuilder<Airlines, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Airlines>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> airlineId_;
    std::shared_ptr<std::string> name_;
    std::shared_ptr<std::string> alias_;
    std::shared_ptr<std::string> iataCode_;
    std::shared_ptr<std::string> icaoCode_;
    std::shared_ptr<std::string> callsign_;
    std::shared_ptr<std::string> country_;
    std::shared_ptr<bool> active_;
    struct MetaData
    {
        const std::string colName_;
        const std::string colType_;
        const std::string colDatabaseType_;
        const ssize_t colLength_;
        const bool isAutoVal_;
        const bool isPrimaryKey_;
        const bool notNull_;
    };
    static const std::vector<MetaData> metaData_;
    bool dirtyFlag_[8]={ false };
  public:
    static const std::string &sqlForFindingByPrimaryKey()
    {
        static const std::string sql="select * from " + tableName + " where airline_id = $1";
        return sql;
    }

    static const std::string &sqlForDeletingByPrimaryKey()
    {
        static const std::string sql="delete from " + tableName + " where airline_id = $1";
        return sql;
    }
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
            sql += "airline_id,";
            ++parametersCount;
        if(dirtyFlag_[1])
        {
            sql += "name,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "alias,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "iata_code,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "icao_code,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "callsign,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "country,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "active,";
            ++parametersCount;
        }
        needSelection=true;
        if(parametersCount > 0)
        {
            sql[sql.length()-1]=')';
            sql += " values (";
        }
        else
            sql += ") values (";

        int placeholder=1;
        char placeholderStr[64];
        size_t n=0;
        sql +="default,";
        if(dirtyFlag_[1])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[2])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[3])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[4])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[5])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[6])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[7])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(parametersCount > 0)
        {
            sql.resize(sql.length() - 1);
        }
        if(needSelection)
        {
            sql.append(") returning *");
        }
        else
        {
            sql.append(1, ')');
        }
        LOG_TRACE << sql;
        return sql;
    }
};
} // namespace mydatabase
} // namespace drogon_model
