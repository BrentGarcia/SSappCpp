/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_SEASONSERVERSTUB_H_
#define JSONRPC_CPP_STUB_SEASONSERVERSTUB_H_

#include <jsonrpccpp/server.h>

class seasonserverstub : public jsonrpc::AbstractServer<seasonserverstub>
{
    public:
        seasonserverstub(jsonrpc::AbstractServerConnector &conn, jsonrpc::serverVersion_t type = jsonrpc::JSONRPC_SERVER_V2) : jsonrpc::AbstractServer<seasonserverstub>(conn, type)
        {
            this->bindAndAddMethod(jsonrpc::Procedure("toJsonFile", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN,  NULL), &seasonserverstub::toJsonFileI);
            this->bindAndAddMethod(jsonrpc::Procedure("addSeriesSeason", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN, "param1",jsonrpc::JSON_OBJECT, NULL), &seasonserverstub::addSeriesSeasonI);
            this->bindAndAddMethod(jsonrpc::Procedure("removeSeriesSeason", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN, "param1",jsonrpc::JSON_STRING, NULL), &seasonserverstub::removeSeriesSeasonI);
            this->bindAndAddMethod(jsonrpc::Procedure("get", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT, "param1",jsonrpc::JSON_STRING, NULL), &seasonserverstub::getI);
            this->bindAndAddMethod(jsonrpc::Procedure("getTitles", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_ARRAY,  NULL), &seasonserverstub::getTitlesI);
        }

        inline virtual void toJsonFileI(const Json::Value &request, Json::Value &response)
        {
            (void)request;
            response = this->toJsonFile();
        }
        inline virtual void addSeriesSeasonI(const Json::Value &request, Json::Value &response)
        {
            response = this->addSeriesSeason(request[0u]);
        }
        inline virtual void removeSeriesSeasonI(const Json::Value &request, Json::Value &response)
        {
            response = this->removeSeriesSeason(request[0u].asString());
        }
        inline virtual void getI(const Json::Value &request, Json::Value &response)
        {
            response = this->get(request[0u].asString());
        }
        inline virtual void getTitlesI(const Json::Value &request, Json::Value &response)
        {
            (void)request;
            response = this->getTitles();
        }
        virtual bool toJsonFile() = 0;
        virtual bool addSeriesSeason(const Json::Value& param1) = 0;
        virtual bool removeSeriesSeason(const std::string& param1) = 0;
        virtual Json::Value get(const std::string& param1) = 0;
        virtual Json::Value getTitles() = 0;
};

#endif //JSONRPC_CPP_STUB_SEASONSERVERSTUB_H_
