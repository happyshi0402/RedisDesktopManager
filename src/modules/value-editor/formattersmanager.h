#pragma once
#include <QAbstractListModel>
#include <QJSValue>

namespace ValueEditor {

class FormattersManager : public QAbstractListModel {
  Q_OBJECT

 public:
  enum Roles { name = Qt::UserRole + 1, version, description, cmd };

 public:
  FormattersManager();

  void loadFormatters();  // TODO make async with callback & invokable

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;

  QVariant data(const QModelIndex& index, int role) const;

  QHash<int, QByteArray> roleNames() const;

  void setPath(const QString& path);

 signals:
  void error(const QString& msg);

 public:
  Q_INVOKABLE void decode(const QString& formatterName, const QByteArray& data,
                          QJSValue jsCallback);

  Q_INVOKABLE void isValid(const QString& formatterName, const QByteArray& data,
                           QJSValue jsCallback);

  Q_INVOKABLE void encode(const QString& formatterName, const QByteArray& data,
                          QJSValue jsCallback);

  Q_INVOKABLE QStringList getPlainList();

  Q_INVOKABLE QString formattersPath();

  Q_INVOKABLE bool isInstalled(const QString& name);

 private:
  void fillMapping();

  QPair<QByteArray, QByteArray> readOutputFromExternalProcess(
      const QStringList& cmd, const QByteArray& processInput,
      const QString& wd);

  QJsonObject readJsonFromExternalProcess(const QStringList& cmd,
                                          const QByteArray& processInput,
                                          const QString& wd);

 private:
  QList<QVariantMap> m_formattersData;
  QHash<QString, int> m_mapping;
  QString m_formattersPath;
};

}  // namespace ValueEditor
