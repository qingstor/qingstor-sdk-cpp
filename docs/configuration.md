# Configuration Guide

## Summary

This SDK uses a structure called "Config" to store and manage configuration.

Except for Access Key, you can also configure the API endpoint for private cloud usage scenario. All available configurable items are listed in the default configuration file.

___Default Configuration File:___

You can copy the default configuration file to your project directory from [here](https://github.com/yunify/qingstor-sdk-net/blob/master/src/Config), and modify it according to your required.

``` yaml
# QingStor services configuration

access_key_id: 'ACCESS_KEY_ID'
secret_access_key: 'SECRET_ACCESS_KEY'

host: 'qingstor.com'
port: 443
protocol: 'https'
connection_retries: 3
timeOutPeriod: 3
```

## Usage

Just create a config structure instance with your API Access Key, and initialize services you need with Init() function of the target service.

### Code Snippet

Create default configuration

``` c
QsConfig qsConfig;
``` 

Change API endpoint

``` c
QsConfig qsConfig;
qsConfig.Protoco = "https";
qsConfig.Host = "api.private.com";
qsConfig.Port = 4433;
```

