# Qt VTK OpenCASCADE 統合プロジェクト

これは、OpenCASCADE Technology (OCC)、Visualization Toolkit (VTK)、およびQtの統合を示す簡単なプロジェクトです。

## 依存関係

*   Qt 5
*   OpenCASCADE Technology (OCC)
*   Visualization Toolkit (VTK)

## コンパイル方法

このプロジェクトは、ビルドシステムとしてCMakeを使用します。

1.  **プロジェクトの構成:**
    ビルドディレクトリを作成し、CMakeを実行します。依存関係が標準の場所にない場合は、パスを指定する必要がある場合があります。

    ```bash
    mkdir build
    cd build
    cmake ..
    ```
    *注意: ジェネレータ（例：「Visual Studio 16 2019」）とQt、VTK、OpenCASCADEへのパスを指定する必要がある場合があります。*

2.  **プロジェクトのビルド:**
    CMakeによって生成されたビルドシステムを使用してソースコードをコンパイルします。

    ```bash
    cmake --build .
    ```
    または、生成されたプロジェクトファイル（例：Visual Studioの`.sln`）をIDEで開き、そこからビルドすることもできます。
