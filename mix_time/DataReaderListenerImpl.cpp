#include <ace/Log_Msg.h>
#include <ace/OS_NS_stdlib.h>

#include "DataReaderListenerImpl.h"
#include "MessengerTypeSupportC.h"
#include "MessengerTypeSupportImpl.h"

#include <iostream>

#include <sys/time.h>

void
DataReaderListenerImpl::on_requested_deadline_missed(
		  DDS::DataReader_ptr /*reader*/,
		    const DDS::RequestedDeadlineMissedStatus& /*status*/)
{
}

void
DataReaderListenerImpl::on_requested_incompatible_qos(
		  DDS::DataReader_ptr /*reader*/,
		    const DDS::RequestedIncompatibleQosStatus& /*status*/)
{
}

void
DataReaderListenerImpl::on_sample_rejected(
		  DDS::DataReader_ptr /*reader*/,
		    const DDS::SampleRejectedStatus& /*status*/)
{
}

void
DataReaderListenerImpl::on_liveliness_changed(
		  DDS::DataReader_ptr /*reader*/,
		    const DDS::LivelinessChangedStatus& /*status*/)
{
}

void DataReaderListenerImpl::on_data_available(DDS::DataReader_ptr reader)
{
	Messenger::MessageDataReader_var reader_i = Messenger::MessageDataReader::_narrow(reader);
	
	if(!reader)
	{
	    ACE_ERROR((LM_ERROR,
		ACE_TEXT("ERROR: %N:%l: on_data_available() -")
		ACE_TEXT("reader  _narrow failed!\n")));
		ACE_OS::exit(-1);
	}

	Messenger::Message message;
	DDS::SampleInfo info;

	DDS::ReturnCode_t error = reader_i ->take_next_sample(message, info);
	
	struct timeval tv;

	if(error ==DDS::RETCODE_OK)
	{
		//std::cout << "SampleInfo.sample_rank = " << info.sample_rank << std::endl;
		//std::cout << "SampleInfo.instance_state = " << info.instance_state << std::endl;

		if(info.valid_data)
		{
			gettimeofday(&tv, NULL);
			long time_stamp = message.stamp;
			long diff = tv.tv_usec - time_stamp;
			/*
			std::cout << "Message: subject    = " << message.subject.in() << std::endl
                      << "         subject_id = " << message.subject_id   << std::endl
	                  << "         from       = " << message.from.in()    << std::endl
	                  << "         count      = " << message.count        << std::endl
	                  << "      time_stamp    = " << message.stamp        << std::endl
	                  << "        time_now    = " << tv.tv_usec           << std::endl
					  << "time_now - time_stamp=" << diff                 << std::endl;
					  */
			std::cout << diff << std::endl;
		}
	}
	else
	{
	    ACE_ERROR((LM_ERROR,
		ACE_TEXT("ERROR: %N:%l: on_data_available() -")
		ACE_TEXT(" take_next_sample failed!\n")));

	}
}
void
DataReaderListenerImpl::on_subscription_matched(
		  DDS::DataReader_ptr /*reader*/,
		    const DDS::SubscriptionMatchedStatus& /*status*/)
{
}

void
DataReaderListenerImpl::on_sample_lost(
		  DDS::DataReader_ptr /*reader*/,
		    const DDS::SampleLostStatus& /*status*/)
{
}
