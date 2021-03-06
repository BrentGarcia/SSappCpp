/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_SEASONCOLLECTIONSTUB_H_
#define JSONRPC_CPP_STUB_SEASONCOLLECTIONSTUB_H_

#include <jsonrpccpp/client.h>

class seasoncollectionstub : public jsonrpc::Client
{
    public:
        seasoncollectionstub(jsonrpc::IClientConnector &conn, jsonrpc::clientVersion_t type = jsonrpc::JSONRPC_CLIENT_V2) : jsonrpc::Client(conn, type) {}

        bool toJsonFile() throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p = Json::nullValue;
            Json::Value result = this->CallMethod("toJsonFile",p);
            if (result.isBool())
                return result.asBool();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        bool addSeriesSeason(const Json::Value& param1) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p.append(param1);
            Json::Value result = this->CallMethod("addSeriesSeason",p);
            if (result.isBool())
                return result.asBool();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        bool removeSeriesSeason(const std::string& param1) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p.append(param1);
            Json::Value result = this->CallMethod("removeSeriesSeason",p);
            if (result.isBool())
                return result.asBool();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        Json::Value get(const std::string& param1) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p.append(param1);
            Json::Value result = this->CallMethod("get",p);
            if (result.isObject())
                return result;
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        Json::Value getTitles() throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p = Json::nullValue;
            Json::Value result = this->CallMethod("getTitles",p);
            if (result.isArray())
                return result;
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
};

#endif //JSONRPC_CPP_STUB_SEASONCOLLECTIONSTUB_H_
