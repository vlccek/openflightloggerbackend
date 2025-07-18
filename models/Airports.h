/**
 *
 *  Airports.h
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

class Airports
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _ident;
        static const std::string _type;
        static const std::string _name;
        static const std::string _latitude_deg;
        static const std::string _longitude_deg;
        static const std::string _elevation_ft;
        static const std::string _continent;
        static const std::string _iso_country;
        static const std::string _iso_region;
        static const std::string _municipality;
        static const std::string _scheduled_service;
        static const std::string _icao_code;
        static const std::string _iata_code;
        static const std::string _gps_code;
        static const std::string _local_code;
        static const std::string _home_link;
        static const std::string _wikipedia_link;
        static const std::string _keywords;
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
    explicit Airports(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit Airports(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    Airports(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    Airports() = default;

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

    /**  For column id  */
    ///Get the value of the column id, returns the default value if the column is null
    const int32_t &getValueOfId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getId() const noexcept;
    ///Set the value of the column id
    void setId(const int32_t &pId) noexcept;

    /**  For column ident  */
    ///Get the value of the column ident, returns the default value if the column is null
    const std::string &getValueOfIdent() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getIdent() const noexcept;
    ///Set the value of the column ident
    void setIdent(const std::string &pIdent) noexcept;
    void setIdent(std::string &&pIdent) noexcept;

    /**  For column type  */
    ///Get the value of the column type, returns the default value if the column is null
    const std::string &getValueOfType() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getType() const noexcept;
    ///Set the value of the column type
    void setType(const std::string &pType) noexcept;
    void setType(std::string &&pType) noexcept;

    /**  For column name  */
    ///Get the value of the column name, returns the default value if the column is null
    const std::string &getValueOfName() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getName() const noexcept;
    ///Set the value of the column name
    void setName(const std::string &pName) noexcept;
    void setName(std::string &&pName) noexcept;

    /**  For column latitude_deg  */
    ///Get the value of the column latitude_deg, returns the default value if the column is null
    const std::string &getValueOfLatitudeDeg() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getLatitudeDeg() const noexcept;
    ///Set the value of the column latitude_deg
    void setLatitudeDeg(const std::string &pLatitudeDeg) noexcept;
    void setLatitudeDeg(std::string &&pLatitudeDeg) noexcept;

    /**  For column longitude_deg  */
    ///Get the value of the column longitude_deg, returns the default value if the column is null
    const std::string &getValueOfLongitudeDeg() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getLongitudeDeg() const noexcept;
    ///Set the value of the column longitude_deg
    void setLongitudeDeg(const std::string &pLongitudeDeg) noexcept;
    void setLongitudeDeg(std::string &&pLongitudeDeg) noexcept;

    /**  For column elevation_ft  */
    ///Get the value of the column elevation_ft, returns the default value if the column is null
    const int32_t &getValueOfElevationFt() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getElevationFt() const noexcept;
    ///Set the value of the column elevation_ft
    void setElevationFt(const int32_t &pElevationFt) noexcept;
    void setElevationFtToNull() noexcept;

    /**  For column continent  */
    ///Get the value of the column continent, returns the default value if the column is null
    const std::string &getValueOfContinent() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getContinent() const noexcept;
    ///Set the value of the column continent
    void setContinent(const std::string &pContinent) noexcept;
    void setContinent(std::string &&pContinent) noexcept;
    void setContinentToNull() noexcept;

    /**  For column iso_country  */
    ///Get the value of the column iso_country, returns the default value if the column is null
    const std::string &getValueOfIsoCountry() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getIsoCountry() const noexcept;
    ///Set the value of the column iso_country
    void setIsoCountry(const std::string &pIsoCountry) noexcept;
    void setIsoCountry(std::string &&pIsoCountry) noexcept;

    /**  For column iso_region  */
    ///Get the value of the column iso_region, returns the default value if the column is null
    const std::string &getValueOfIsoRegion() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getIsoRegion() const noexcept;
    ///Set the value of the column iso_region
    void setIsoRegion(const std::string &pIsoRegion) noexcept;
    void setIsoRegion(std::string &&pIsoRegion) noexcept;

    /**  For column municipality  */
    ///Get the value of the column municipality, returns the default value if the column is null
    const std::string &getValueOfMunicipality() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getMunicipality() const noexcept;
    ///Set the value of the column municipality
    void setMunicipality(const std::string &pMunicipality) noexcept;
    void setMunicipality(std::string &&pMunicipality) noexcept;
    void setMunicipalityToNull() noexcept;

    /**  For column scheduled_service  */
    ///Get the value of the column scheduled_service, returns the default value if the column is null
    const bool &getValueOfScheduledService() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<bool> &getScheduledService() const noexcept;
    ///Set the value of the column scheduled_service
    void setScheduledService(const bool &pScheduledService) noexcept;

    /**  For column icao_code  */
    ///Get the value of the column icao_code, returns the default value if the column is null
    const std::string &getValueOfIcaoCode() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getIcaoCode() const noexcept;
    ///Set the value of the column icao_code
    void setIcaoCode(const std::string &pIcaoCode) noexcept;
    void setIcaoCode(std::string &&pIcaoCode) noexcept;
    void setIcaoCodeToNull() noexcept;

    /**  For column iata_code  */
    ///Get the value of the column iata_code, returns the default value if the column is null
    const std::string &getValueOfIataCode() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getIataCode() const noexcept;
    ///Set the value of the column iata_code
    void setIataCode(const std::string &pIataCode) noexcept;
    void setIataCode(std::string &&pIataCode) noexcept;
    void setIataCodeToNull() noexcept;

    /**  For column gps_code  */
    ///Get the value of the column gps_code, returns the default value if the column is null
    const std::string &getValueOfGpsCode() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getGpsCode() const noexcept;
    ///Set the value of the column gps_code
    void setGpsCode(const std::string &pGpsCode) noexcept;
    void setGpsCode(std::string &&pGpsCode) noexcept;
    void setGpsCodeToNull() noexcept;

    /**  For column local_code  */
    ///Get the value of the column local_code, returns the default value if the column is null
    const std::string &getValueOfLocalCode() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getLocalCode() const noexcept;
    ///Set the value of the column local_code
    void setLocalCode(const std::string &pLocalCode) noexcept;
    void setLocalCode(std::string &&pLocalCode) noexcept;
    void setLocalCodeToNull() noexcept;

    /**  For column home_link  */
    ///Get the value of the column home_link, returns the default value if the column is null
    const std::string &getValueOfHomeLink() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getHomeLink() const noexcept;
    ///Set the value of the column home_link
    void setHomeLink(const std::string &pHomeLink) noexcept;
    void setHomeLink(std::string &&pHomeLink) noexcept;
    void setHomeLinkToNull() noexcept;

    /**  For column wikipedia_link  */
    ///Get the value of the column wikipedia_link, returns the default value if the column is null
    const std::string &getValueOfWikipediaLink() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getWikipediaLink() const noexcept;
    ///Set the value of the column wikipedia_link
    void setWikipediaLink(const std::string &pWikipediaLink) noexcept;
    void setWikipediaLink(std::string &&pWikipediaLink) noexcept;
    void setWikipediaLinkToNull() noexcept;

    /**  For column keywords  */
    ///Get the value of the column keywords, returns the default value if the column is null
    const std::string &getValueOfKeywords() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getKeywords() const noexcept;
    ///Set the value of the column keywords
    void setKeywords(const std::string &pKeywords) noexcept;
    void setKeywords(std::string &&pKeywords) noexcept;
    void setKeywordsToNull() noexcept;


    static size_t getColumnNumber() noexcept {  return 19;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;
    /// Relationship interfaces
  private:
    friend drogon::orm::Mapper<Airports>;
    friend drogon::orm::BaseBuilder<Airports, true, true>;
    friend drogon::orm::BaseBuilder<Airports, true, false>;
    friend drogon::orm::BaseBuilder<Airports, false, true>;
    friend drogon::orm::BaseBuilder<Airports, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Airports>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> id_;
    std::shared_ptr<std::string> ident_;
    std::shared_ptr<std::string> type_;
    std::shared_ptr<std::string> name_;
    std::shared_ptr<std::string> latitudeDeg_;
    std::shared_ptr<std::string> longitudeDeg_;
    std::shared_ptr<int32_t> elevationFt_;
    std::shared_ptr<std::string> continent_;
    std::shared_ptr<std::string> isoCountry_;
    std::shared_ptr<std::string> isoRegion_;
    std::shared_ptr<std::string> municipality_;
    std::shared_ptr<bool> scheduledService_;
    std::shared_ptr<std::string> icaoCode_;
    std::shared_ptr<std::string> iataCode_;
    std::shared_ptr<std::string> gpsCode_;
    std::shared_ptr<std::string> localCode_;
    std::shared_ptr<std::string> homeLink_;
    std::shared_ptr<std::string> wikipediaLink_;
    std::shared_ptr<std::string> keywords_;
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
    bool dirtyFlag_[19]={ false };
  public:
    static const std::string &sqlForFindingByPrimaryKey()
    {
        static const std::string sql="select * from " + tableName + " where id = $1";
        return sql;
    }

    static const std::string &sqlForDeletingByPrimaryKey()
    {
        static const std::string sql="delete from " + tableName + " where id = $1";
        return sql;
    }
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
        if(dirtyFlag_[0])
        {
            sql += "id,";
            ++parametersCount;
        }
        if(dirtyFlag_[1])
        {
            sql += "ident,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "type,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "name,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "latitude_deg,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "longitude_deg,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "elevation_ft,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "continent,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "iso_country,";
            ++parametersCount;
        }
        if(dirtyFlag_[9])
        {
            sql += "iso_region,";
            ++parametersCount;
        }
        if(dirtyFlag_[10])
        {
            sql += "municipality,";
            ++parametersCount;
        }
        if(dirtyFlag_[11])
        {
            sql += "scheduled_service,";
            ++parametersCount;
        }
        if(dirtyFlag_[12])
        {
            sql += "icao_code,";
            ++parametersCount;
        }
        if(dirtyFlag_[13])
        {
            sql += "iata_code,";
            ++parametersCount;
        }
        if(dirtyFlag_[14])
        {
            sql += "gps_code,";
            ++parametersCount;
        }
        if(dirtyFlag_[15])
        {
            sql += "local_code,";
            ++parametersCount;
        }
        if(dirtyFlag_[16])
        {
            sql += "home_link,";
            ++parametersCount;
        }
        if(dirtyFlag_[17])
        {
            sql += "wikipedia_link,";
            ++parametersCount;
        }
        if(dirtyFlag_[18])
        {
            sql += "keywords,";
            ++parametersCount;
        }
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
        if(dirtyFlag_[0])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
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
        if(dirtyFlag_[8])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[9])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[10])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[11])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[12])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[13])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[14])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[15])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[16])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[17])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[18])
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
