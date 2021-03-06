#ifndef COMMON_H_SD3DSFSDD
#define COMMON_H_SD3DSFSDD

#include <memory>
#include <vector>
#include <string>
#include <cassert>
#include <tuple>

#include <QObject>
#include <QtCore/qstring.h> 
#include <QTime>

#ifndef IN
#define  IN
#define  OUT
#define  INOUT
#endif

#if 0
std::vector<std::string> split(const std::string& line, const std::string& seperator = " ", 
		const std::string& quotation = "\"");

std::string&   replace_all(std::string&   str, const   std::string&   old_value, const   std::string&   new_value);
std::string&   replace_all_distinct(std::string&   str, const   std::string&   old_value, const  std::string&   new_value);
#endif
enum class TypeMarket : char
{
    SZ = 0,
    SH
};

enum class TypeOrderCategory : char
{
    BUY = 0,
    SELL = 1,
    RQ_BUY,
    RQ_SELL,
    BQ_HQ,
    SQ_HQ,
    CQ_HQ,
};
// 0资金  1股份   2当日委托  3当日成交     4可撤单   5股东代码  6融资余额   7融券余额  8可融证券</param>
enum class TypeQueryCategory : char
{
    CAPITAL = 0,
    STOCK = 1,
    TODAY_DELEGATE = 2,
    TODAY_FILL = 3,
    CAN_RECALL_ORDER,
    SHARED_HOLDER_CODE = 5,
    RZYE,
    RQYE,
    KRZQ,
};

enum class TypeUserLevel : char
{
    NORMAL = 1,
};

enum class TypeBroker : char
{
    FANG_ZHENG = 1,
    PING_AN,
	ZHONGXIN,
    ZHONGYGJ,
};

enum class TypeTask : char
{
    INFLECTION_BUY = 0, 
    BREAKUP_BUY,
    BATCHES_BUY,

    INFLECTION_SELL,  //3
    BREAK_SELL,
    FOLLOW_SELL,
    BATCHES_SELL,

	EQUAL_SECTION,
};

enum class TypeQuoteLevel : char
{
    PRICE_CUR = 0,
    PRICE_BUYSELL_1,
    PRICE_BUYSELL_2,
    PRICE_BUYSELL_3,
    PRICE_BUYSELL_4,
    PRICE_BUYSELL_5,
};

enum class TaskStatChangeType : char
{
    CUR_PRICE_CHANGE = 0,
    CUR_STATE_CHANGE,
};

enum class TaskCurrentState : char
{
    STOP = 0,
    TORUN,   
    WAITTING, /* not stop, and is not in between start time and end time*/
    RUNNING,
};

  
enum class TypeEqSection : char
{
	STOP = 0,
	SELL,
	NOOP,
	BUY,
	CLEAR,
};

struct T_SectionAutom
{
	TypeEqSection  section_type;
	double represent_price;
	T_SectionAutom() : section_type(TypeEqSection::NOOP), represent_price(0.0){}
	T_SectionAutom(TypeEqSection type, double resp_price) : section_type(type), represent_price(resp_price){}
};

struct T_AccountData
{
    char shared_holder_code[64]; 
    char name[64];
    TypeMarket type;
    char capital_code[64]; 
    char seat_code[64];
    char rzrq_tag[64];  //融资融券 标识
};

struct T_UserInformation
{
    int id;
    int level;
    std::string name;
    std::string nick_name;
    std::string password;
    int account_id;
    std::string account_no;
    std::string remark;
    T_UserInformation() : id(0), level(0), account_id(0){}
    
    T_UserInformation &operator = (const T_UserInformation&lh)
    {
        id = lh.id; level = lh.level; name = lh.name; nick_name = lh.nick_name;
        password = lh.password; account_id = lh.account_id; account_no = lh.account_no; remark = lh.remark;  
        return *this;
    }
};

struct T_AccountInformation
{
    int id;
    std::string account_no;
    std::string trade_acc_no;
    std::string trade_pwd;
    std::string comm_pwd;
    int broker_id; 
    std::string department_id; 
    std::string remark;
    T_AccountInformation() : id(-1), broker_id(-1) {}
};

struct T_PositionData
{
    std::string code;
    std::string pinyin;
    int total;
    int avaliable;
    double cost;
    double value;
    double profit;
    double profit_percent;
    T_PositionData() : code(), pinyin(), total(0),avaliable(0), cost(0.0), value(0.0), profit(0.0), profit_percent(0.0){}
    T_PositionData(const T_PositionData &lh) : code(lh.code), pinyin(lh.pinyin), total(lh.total),avaliable(lh.avaliable), cost(lh.cost), value(lh.value), profit(lh.profit), profit_percent(lh.profit_percent){}
    T_PositionData(const T_PositionData &&lh) : code(std::move(lh.code)), pinyin(std::move(lh.pinyin)), total(lh.total),avaliable(lh.avaliable), cost(lh.cost), value(lh.value), profit(lh.profit), profit_percent(lh.profit_percent){}
};

class  QuotesData
{
public:
    int64_t time_stamp;
	double cur_price;
    double active_degree;
    double price_b_1;
    double price_s_1;
    double price_b_2;
    double price_s_2;
    double price_b_3;
    double price_s_3;
    double price_b_4;
    double price_s_4;
    double price_b_5;
    double price_s_5;
    QuotesData() 
        : time_stamp(0)
        , cur_price(0.0)  
        , active_degree(0.0)
        , price_b_1(0.0)
        , price_s_1(0.0)
        , price_b_2(0.0)
        , price_s_2(0.0)
        , price_b_3(0.0)
        , price_s_3(0.0)
        , price_b_4(0.0)
        , price_s_4(0.0)
        , price_b_5(0.0)
        , price_s_5(0.0)
    {
    }
};

class Buffer
{
public:

    explicit Buffer(unsigned int size=64) : size_(size), p_data_(nullptr) 
    {
        p_data_ = new char[size + 1];
        p_data_[size] = '\0';
    }
    explicit Buffer(const char* p_str, unsigned int size) 
    {
        assert(p_str);
        p_data_ = new char[size + 1];
        size_ = size;
        memcpy(p_data_, p_str, size);
        p_data_[size] = '\0';
    } 

    ~Buffer(){ if( p_data_ ) delete p_data_; p_data_ = nullptr;};

    char * data() { return p_data_; }
    const char *c_data() const {return p_data_;}
    unsigned int size() const {return size_;}

private:

    Buffer(Buffer&);
    Buffer& operator = (Buffer&);

    unsigned int size_;
    char *p_data_;
};

struct T_BrokerInfo
{
    int         id;
    TypeBroker  type; 
    std::string ip;
    int         port;
    std::string com_ver;
    std::string remark; // name: 方正;  平安 ...
   /* T_BrokerInfo(){}
    T_BrokerInfo(T_BrokerInfo &&val) : id(val.id), type(val.type), ip(std::move(val.ip)), port(val.port), com_ver(std::move(val.com_ver)), remark(std::move(val.remark))
    { 
    }*/
    //bool operator (T_BrokerInfo &lh, T_BrokerInfo &rh) { return lh.id < rh.id; }
    T_BrokerInfo& operator = (T_BrokerInfo& lh)
    {
        id = lh.id; type = lh.type; ip = lh.ip; port = lh.port; com_ver = lh.com_ver; remark = lh.remark;
        return *this;
    }
};

bool compare(T_BrokerInfo &lh, T_BrokerInfo &rh);

struct  T_UserAccountInfo
{
    int level_;
    int account_id;
    int broker_id_;
    //std::string broker_interface_version_;
    std::string account_no_in_broker_;
    std::string trade_no_in_broker_;
    std::string trade_pwd_;
    std::string comm_pwd_;
    std::string department_id_;
    T_UserAccountInfo(): level_(0), account_id(0), broker_id_(0){}

    T_UserAccountInfo& operator = (T_UserAccountInfo lh)
    {
        level_ = lh.level_; account_id = lh.account_id; broker_id_ = lh.broker_id_; account_no_in_broker_ = lh.account_no_in_broker_;
        trade_no_in_broker_ = lh.trade_no_in_broker_; trade_pwd_ = lh.trade_pwd_; comm_pwd_ = lh.comm_pwd_; 
        department_id_ = lh.department_id_;
        return *this;
    }
};

struct T_SectionTask
{ 
	double raise_percent;
	double fall_percent;
	double raise_infection;
	double fall_infection; 
	int  multi_qty;
	double max_trig_price;
	double min_trig_price;
	std::string sections_info; //format: section0_type$section0_price#section1_type$section1_price
	bool is_original;
	T_SectionTask():raise_percent(0.0), fall_percent(0.0), raise_infection(0.0), fall_infection(0.0)
		, multi_qty(0),max_trig_price(0.0), min_trig_price(0.0), sections_info(), is_original(true)
	{
	}
};

struct T_TaskInformation
{
    unsigned int id;
    TypeTask  type;
    std::string stock;        // TEXT not null,
    std::string stock_pinyin; // TEXT 

	double alert_price;       // DOUBLE, 
	bool back_alert_trigger;  // 是否重回则触发
	double rebounce;          // 反弹或回撤 百分值
	int continue_second;      // 0-- not open >0 -- open
	double step;              // 阶梯幅度(以后每涨,以后每降) 百分值
	unsigned int quantity;    // 买入数量, 每次数量
	T_SectionTask secton_task;
	int target_price_level;   // 0--即时价  1--买一和卖一 2--买二和卖二 3--买三和卖三 ...
	int start_time; 
	int end_time;
	bool is_loop;
    int  state; // 0-- stop    1-- to run
    int  bs_times;               // 卖出次数
    T_TaskInformation() : id(0), type(TypeTask::BREAK_SELL), alert_price(0),back_alert_trigger(0), rebounce(0), continue_second(0), step(0), quantity(0), target_price_level(0), start_time(0), end_time(0), is_loop(0), state(0), bs_times(0) {} 
     
    T_TaskInformation(T_TaskInformation& lh) : id(lh.id), type(lh.type), stock(lh.stock), stock_pinyin(lh.stock_pinyin), alert_price(lh.alert_price), back_alert_trigger(lh.back_alert_trigger)
        , rebounce(lh.rebounce), continue_second(lh.continue_second), step(lh.step), quantity(lh.quantity), target_price_level(lh.target_price_level)
        , start_time(lh.start_time), end_time(lh.end_time), is_loop(lh.is_loop), state(lh.state), bs_times(lh.bs_times) { }
};

struct StockPrice
{
    std::string code;
    std::string cur_price;
    //std::string active_degree;
    std::string price_b_1;
    std::string price_s_1;
    std::string price_b_2;
    std::string price_s_2;
    std::string price_b_3;
    std::string price_s_3;
    std::string price_b_4;
    std::string price_s_4;
    std::string price_b_5;
    std::string price_s_5;
    __int64 time_stamp;
};

struct T_StockCodeName
{
    std::string code;
    std::string name;
    T_StockCodeName(const std::string &cd, const std::string &nm) : code(cd), name(nm)
    { 
    }
};

struct T_Capital
{
    double remain;
    double available;
    double total;
};
//struct T_StockPosition
//{
//    std::string  code;
//    unsigned int position;
//};

QString ToQString(TypeTask val);
QString ToQString(TypeQuoteLevel val);
QString ToQString(TaskCurrentState val);

void Delay(unsigned short mseconds);

bool Equal(double lh, double rh);

QTime Int2Qtime(int hhmmss);

bool IsStrAlpha(const std::string& str);
bool IsStrNum(const std::string& str);

//bool Equal(double lh, double rh, double esp=1e-4);
//============================

std::string TagOfLog();
std::string TagOfOrderLog();


std::tuple<int, std::string> CurrentDateTime();

#define USE_TRADE_FLAG

#endif