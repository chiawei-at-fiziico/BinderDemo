#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <utils/Log.h>

#define LOG_TAG "trustzone"

using namespace android;

class ITrustZoneService : public IInterface
{
    public:
        enum {
            ADD = IBinder::FIRST_CALL_TRANSACTION
        };

        DECLARE_META_INTERFACE(TrustZoneService);

        virtual int32_t add(int32_t val1, int32_t val2) = 0;
};

class BpTrustZoneService : public BpInterface<ITrustZoneService>
{
    public:
        BpTrustZoneService(const sp<IBinder>& impl)
            : BpInterface<ITrustZoneService>(impl)
        {
        }

        virtual int32_t add(int32_t val1, int32_t val2) {
            Parcel data, reply;
            data.writeInterfaceToken(
                    ITrustZoneService::getInterfaceDescriptor());
            data.writeInt32(val1);
            data.writeInt32(val2);
            remote()->transact(ADD, data, &reply);
            int32_t sum;
            status_t err = reply.readInt32(&sum);
            return sum;
        }
};

class BnTrustZoneService : public BnInterface<ITrustZoneService>
{
    virtual status_t onTransact(uint32_t code, const Parcel& data,
            Parcel* reply, uint32_t flags = 0) {
        //data.checkInterface(this);
        switch (code) {
            case ADD: {
                CHECK_INTERFACE(ITrustZoneService, data, reply);
                int32_t val1 = data.readInt32();
                int32_t val2 = data.readInt32();
                int32_t sum = val1 + val2;
                ALOGD("ADD %i %i = %i", val1, val2, sum);
                reply->writeNoException();
                reply->writeInt32(sum);
                return NO_ERROR;
            } break;
            default:
                return BBinder::onTransact(code, data, reply, flags);
        }
    }
};

IMPLEMENT_META_INTERFACE(
        TrustZoneService, "com.fiziico.trustzone.ITrustZoneService");

class TrustZoneProxy : public BnTrustZoneService
{
    virtual int32_t add(int32_t val1, int32_t val2) {
        return val1 + val2;
    }
};

int main()
{
    defaultServiceManager()->addService(
            String16("com.fiziico.trustzone"), new TrustZoneProxy());
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();

    return 0;
}
