const path = require("path");
let CopyPlugin = require("copy-webpack-plugin");
let ReactRefresh = require("@pmmmwh/react-refresh-webpack-plugin");

let mode = process.env.NODE_ENV === "production" ? "production" : "development";
let dev = mode === "development";

module.exports = {
  mode,
  entry: "./src/Index.bs.js",
  // If you ever want to use webpack during development, change 'production'
  // to 'development' as per webpack documentation. Again, you don't have to
  // use webpack or any other bundler during development! Recheck README if
  // you didn't know this
  output: {
    path: path.join(__dirname, "dist"),
    filename: "bundle.js",
  },
  devServer: {
    contentBase: "./dist",
    port: 3000,
    hot: true,
    historyApiFallback: true,
  },
  module: {
    rules: [{ test: /\.css/, use: ["style-loader", "css-loader"] }],
  },
  plugins: [
    new CopyPlugin({
      patterns: [{ from: "public/index.html", to: "" }],
    }),
    dev && new ReactRefresh(),
  ].filter(Boolean),
};
