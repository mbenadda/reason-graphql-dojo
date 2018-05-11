// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE
'use strict';

var Js_dict = require("bs-platform/lib/js/js_dict.js");
var ApolloLinks = require("reason-apollo/src/ApolloLinks.bs.js");
var ReasonApollo = require("reason-apollo/src/ReasonApollo.bs.js");
var ApolloInMemoryCache = require("reason-apollo/src/ApolloInMemoryCache.bs.js");

var inMemoryCache = ApolloInMemoryCache.createInMemoryCache(/* None */0, /* None */0, /* () */0);

var httpLink = ApolloLinks.createHttpLink("https://api.github.com/graphql", /* None */0, /* None */0, /* Some */[Js_dict.fromList(/* :: */[
            /* tuple */[
              "Authorization",
              "bearer 7746e7c83c4ade9b85d328dedbc29b29619094e6"
            ],
            /* [] */0
          ])], /* None */0, /* None */0, /* () */0);

var instance = ReasonApollo.createApolloClient(httpLink, inMemoryCache, /* None */0, /* None */0, /* None */0, /* None */0, /* () */0);

exports.inMemoryCache = inMemoryCache;
exports.httpLink = httpLink;
exports.instance = instance;
/* inMemoryCache Not a pure module */
